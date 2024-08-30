//
// Created by 杜建璋 on 2024/7/13.
//

#include "executor/share/arithmetic/multiplication/MulShareExecutor.h"
#include "utils/MpiUtils.h"
#include "utils/MathUtils.h"
#include "utils/Log.h"

MulShareExecutor::MulShareExecutor(int64_t x, int l) {
    // data
    _x = x;
    _x1 = MathUtils::rand64();
    _x0 = _x - _x1;

    _l = l >= 64 ? 64 : (l >= 32 ? 32 : (l >= 16 ? 16 : (l >= 8 ? 8 : 4)));
}

void MulShareExecutor::compute() {
    int64_t start, end, end1;
    if (_benchmarkLevel >= BenchmarkLevel::GENERAL) {
        start = System::currentTimeMillis();
    }
    // MT
    obtainMultiplicationTriple();
    if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
        end = System::currentTimeMillis();
        if (_isLogBenchmark) {
            Log::i(tag() + " Triple computation time: " + std::to_string(end - start) + " ms.");
        }
    }
    // process
    process();
    if (_benchmarkLevel >= BenchmarkLevel::GENERAL) {
        end1 = System::currentTimeMillis();
        if (_benchmarkLevel == BenchmarkLevel::DETAILED && _isLogBenchmark) {
            Log::i(tag() + " MPI transmission and synchronization time: " + std::to_string(_mpiTime) + " ms.");
        }
        if (_isLogBenchmark) {
            Log::i(tag() + " Entire computation time: " + std::to_string(end1 - start) + " ms.");
        }
        _entireComputationTime = end1 - start;
    }
}

void MulShareExecutor::process() {
    int64_t x0, y0, *self, *other;
    self = MpiUtils::rank() == 0 ? &x0 : &y0;
    other = MpiUtils::rank() == 0 ? &y0 : &x0;
    *self = _x0;
    if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
        MpiUtils::exchange(&_x1, other, _mpiTime);
    } else {
        MpiUtils::exchange(&_x1, other);
    }
    int64_t e0 = x0 - _a0;
    int64_t f0 = y0 - _b0;
    int64_t e1, f1;
    if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
        MpiUtils::exchange(&e0, &e1, _mpiTime);
        MpiUtils::exchange(&f0, &f1, _mpiTime);
    } else {
        MpiUtils::exchange(&e0, &e1);
        MpiUtils::exchange(&f0, &f1);
    }
    int64_t e = e0 + e1;
    int64_t f = f0 + f1;
    int64_t z0 = MpiUtils::rank() * e * f + f * _a0 + e * _b0 + _c0;
    int64_t z1;
    if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
        MpiUtils::exchange(&z0, &z1, _mpiTime);
    } else {
        MpiUtils::exchange(&z0, &z1);
    }
    _res = MathUtils::ringMod(z0 + z1, _l);
}
