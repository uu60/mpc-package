//
// Created by 杜建璋 on 2024/8/29.
//

#include "executor/share/boolean/and/AbstractAndShareExecutor.h"
#include "utils/Math.h"
#include "utils/Mpi.h"
#include "executor/bmt/RsaOtTripleGenerator.h"

AbstractAndShareExecutor::AbstractAndShareExecutor(bool x, bool y) {
    bool bm = _benchmarkLevel == BenchmarkLevel::DETAILED;
    if (!Mpi::isCalculator()) {
        bool x1 = Math::rand32(0, 1);
        bool x0 = x1 xor x;
        bool y1 = Math::rand32(0, 1);
        bool y0 = y1 xor y;
        Mpi::sendTo(&x0, 0, _mpiTime, bm);
        Mpi::sendTo(&y0, 0, _mpiTime, bm);
        Mpi::sendTo(&x1, 1, _mpiTime, bm);
        Mpi::sendTo(&y1, 1, _mpiTime, bm);
    } else {
        // data
        Mpi::recvFrom(&_xi, Mpi::TASK_PUBLISHER_RANK, _mpiTime, bm);
        Mpi::recvFrom(&_yi, Mpi::TASK_PUBLISHER_RANK, _mpiTime, bm);
    }
}

void AbstractAndShareExecutor::compute() {
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
}

std::string AbstractAndShareExecutor::tag() const {
    return "[And Boolean Share]";
}

void AbstractAndShareExecutor::process() {
    /*
     * For variable name description, please refer to
     * RsaOtMultiplicationShareExecution.cpp
     * */
    bool bm = _benchmarkLevel == BenchmarkLevel::DETAILED;
    if (Mpi::isCalculator()) {
        bool ei = _ai xor _xi;
        bool fi = _bi xor _yi;
        bool eo, fo;
        Mpi::exchange(&ei, &eo, _mpiTime, bm);
        Mpi::exchange(&fi, &fo, _mpiTime, bm);
        bool e = ei xor eo;
        bool f = fi xor fo;
        bool z0 = Mpi::rank() * e * f xor f * _ai xor e * _bi xor _ci;
        Mpi::sendTo(&z0, Mpi::TASK_PUBLISHER_RANK, _mpiTime, bm);
    } else {
        bool z0, z1;
        Mpi::recvFrom(&z0, 0, _mpiTime, bm);
        Mpi::recvFrom(&z1, 1, _mpiTime, bm);
        _result = z0 xor z1;
    }
}
