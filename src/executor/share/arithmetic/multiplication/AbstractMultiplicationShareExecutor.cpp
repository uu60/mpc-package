//
// Created by 杜建璋 on 2024/7/13.
//

#include "executor/share/arithmetic/multiplication/AbstractMultiplicationShareExecutor.h"
#include "utils/Mpi.h"
#include "utils/Math.h"
#include "utils/Log.h"

AbstractMultiplicationShareExecutor::AbstractMultiplicationShareExecutor(int64_t x, int64_t y, int l) {
    bool bm = _benchmarkLevel == BenchmarkLevel::DETAILED;
    // distribute data
    if (!Mpi::isCalculator()) {
        int64_t x1 = Math::rand64();
        int64_t x0 = x - x1;
        int64_t y1 = Math::rand64();
        int64_t y0 = y - y1;
        Mpi::sendTo(&x0, 0, _mpiTime, bm);
        Mpi::sendTo(&y0, 0, _mpiTime, bm);
        Mpi::sendTo(&x1, 1, _mpiTime, bm);
        Mpi::sendTo(&y1, 1, _mpiTime, bm);
    } else {
        // data
        Mpi::recvFrom(&_xi, Mpi::TASK_PUBLISHER_RANK, _mpiTime, bm);
        Mpi::recvFrom(&_yi, Mpi::TASK_PUBLISHER_RANK, _mpiTime, bm);

        _l = l >= 64 ? 64 : (l >= 32 ? 32 : (l >= 16 ? 16 : (l >= 8 ? 8 : 4)));
    }
}

void AbstractMultiplicationShareExecutor::compute() {
    int64_t start, end, end1;
    if (_benchmarkLevel >= BenchmarkLevel::GENERAL) {
        start = System::currentTimeMillis();
    }
    if (Mpi::isCalculator()) {
        // MT
        obtainMultiplicationTriple();
        if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
            end = System::currentTimeMillis();
            if (_isLogBenchmark) {
                Log::i(tag() + " Triple computation time: " + std::to_string(end - start) + " ms.");
            }
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

void AbstractMultiplicationShareExecutor::process() {
    bool bm = _benchmarkLevel == BenchmarkLevel::DETAILED;
    if (Mpi::isCalculator()) {
        int64_t ei = _xi - _ai;
        int64_t fi = _yi - _bi;
        int64_t eo, fo;
        Mpi::exchange(&ei, &eo, _mpiTime, bm);
        Mpi::exchange(&fi, &fo, _mpiTime, bm);
        int64_t e = ei + eo;
        int64_t f = fi + fo;
        int64_t zi = Mpi::rank() * e * f + f * _ai + e * _bi + _ci;
        Mpi::sendTo(&zi, Mpi::TASK_PUBLISHER_RANK, _mpiTime, bm);
    } else {
        int64_t z0, z1;
        Mpi::recvFrom(&z0, 0, _mpiTime, bm);
        Mpi::recvFrom(&z1, 1, _mpiTime, bm);
        _result = Math::ringMod(z0 + z1, _l);
    }
}
