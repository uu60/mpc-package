//
// Created by 杜建璋 on 2024/7/13.
//

#include "executor/share/arithmetic/multiplication/AbstractMultiplicationShareExecutor.h"
#include "utils/Mpi.h"
#include "utils/Math.h"
#include "utils/Log.h"

AbstractMultiplicationShareExecutor::AbstractMultiplicationShareExecutor(int64_t x, int64_t y, int l) : IntShareExecutor(x, y, l) {}

AbstractMultiplicationShareExecutor::AbstractMultiplicationShareExecutor(int64_t xi, int64_t yi, int l, bool dummy) : IntShareExecutor(xi, yi, l, dummy) {}

AbstractMultiplicationShareExecutor* AbstractMultiplicationShareExecutor::execute(bool reconstruct) {
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
    process(reconstruct);
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

    return this;
}

void AbstractMultiplicationShareExecutor::process(bool reconstruct) {
    bool detailed = _benchmarkLevel == BenchmarkLevel::DETAILED;
    if (Mpi::isCalculator()) {
        int64_t ei = _xi - _ai;
        int64_t fi = _yi - _bi;
        int64_t eo, fo;
        Mpi::exchangeC(&ei, &eo, _mpiTime, detailed);
        Mpi::exchangeC(&fi, &fo, _mpiTime, detailed);
        int64_t e = ei + eo;
        int64_t f = fi + fo;
        _zi = Mpi::rank() * e * f + f * _ai + e * _bi + _ci;
        _result = _zi;
    }
    if (reconstruct) {
        this->reconstruct();
    }
}

AbstractMultiplicationShareExecutor *AbstractMultiplicationShareExecutor::reconstruct() {
    // do nothing
    return this;
}
