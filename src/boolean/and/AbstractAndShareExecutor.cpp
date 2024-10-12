//
// Created by 杜建璋 on 2024/8/29.
//

#include "boolean/and/AbstractAndShareExecutor.h"
#include "utils/Mpi.h"

AbstractAndShareExecutor::AbstractAndShareExecutor(bool x, bool y) : BoolShareExecutor(x, y) {}

AbstractAndShareExecutor::AbstractAndShareExecutor(bool xi, bool yi, bool dummy) : BoolShareExecutor(xi, yi, dummy) {}

AbstractAndShareExecutor* AbstractAndShareExecutor::execute(bool reconstruct) {
    // BMT
    int64_t start, end, end1;
    if (_benchmarkLevel >= BenchmarkLevel::GENERAL) {
        start = System::currentTimeMillis();
    }
    if (Mpi::isServer()) {
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
    if (Mpi::isServer()) {
        bool ei = _ai ^ _xi;
        bool fi = _bi ^ _yi;
        bool eo, fo;
        Mpi::sexch(&ei, &eo, _mpiTime, detailed);
        Mpi::sexch(&fi, &fo, _mpiTime, detailed);
        bool e = ei ^ eo;
        bool f = fi ^ fo;
        _zi = Mpi::rank() * e * f ^ f * _ai ^ e * _bi ^ _ci;
        _result = _zi;
    }
    if (reconstruct) {
        this->reconstruct();
    }
}
