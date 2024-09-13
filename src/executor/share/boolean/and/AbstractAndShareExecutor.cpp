//
// Created by 杜建璋 on 2024/8/29.
//

#include "executor/share/boolean/and/AbstractAndShareExecutor.h"
#include "utils/Mpi.h"

AbstractAndShareExecutor::AbstractAndShareExecutor(bool x, bool y) : BoolShareExecutor(x, y) {}

AbstractAndShareExecutor::AbstractAndShareExecutor(bool x, bool y, bool dummy) : BoolShareExecutor(x, y, dummy) {}

AbstractAndShareExecutor* AbstractAndShareExecutor::execute(bool reconstruct) {
    // BMT
    int64_t start, end, end1;
    if (_benchmarkLevel >= BenchmarkLevel::GENERAL) {
        start = System::currentTimeMillis();
    }
    if (Mpi::isCalculator()) {
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

std::string AbstractAndShareExecutor::tag() const {
    return "[And Boolean Share]";
}

void AbstractAndShareExecutor::process(bool reconstruct) {
    /*
     * For variable name description, please refer to
     * RsaOtMultiplicationShareExecution.cpp
     * */
    bool detailed = _benchmarkLevel == BenchmarkLevel::DETAILED;
    if (Mpi::isCalculator()) {
        bool ei = _ai xor _xi;
        bool fi = _bi xor _yi;
        bool eo, fo;
        Mpi::exchangeC(&ei, &eo, _mpiTime, detailed);
        Mpi::exchangeC(&fi, &fo, _mpiTime, detailed);
        bool e = ei xor eo;
        bool f = fi xor fo;
        _zi = Mpi::rank() * e * f xor f * _ai xor e * _bi xor _ci;
        _result = _zi;
    }
    if (reconstruct) {
        this->reconstruct();
    }
}
