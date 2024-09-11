//
// Created by 杜建璋 on 2024/8/29.
//

#include "executor/share/boolean/and/AbstractAndShareExecutor.h"
#include "utils/Mpi.h"

AbstractAndShareExecutor::AbstractAndShareExecutor(bool x, bool y) : AbstractBoolShareExecutor(x, y) {}

AbstractAndShareExecutor::AbstractAndShareExecutor(bool x, bool y, bool dummy) : AbstractBoolShareExecutor(x, y, dummy) {}

AbstractAndShareExecutor* AbstractAndShareExecutor::execute() {
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

    return this;
}

std::string AbstractAndShareExecutor::tag() const {
    return "[And Boolean Share]";
}

void AbstractAndShareExecutor::process() {
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
        bool z0 = Mpi::rank() * e * f xor f * _ai xor e * _bi xor _ci;
        Mpi::sendTo(&z0, Mpi::DATA_HOLDER_RANK, _mpiTime, detailed);
    } else {
        bool z0, z1;
        Mpi::recvFrom(&z0, 0, _mpiTime, detailed);
        Mpi::recvFrom(&z1, 1, _mpiTime, detailed);
        _result = z0 xor z1;
    }
}
