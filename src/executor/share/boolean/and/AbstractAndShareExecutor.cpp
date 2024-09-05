//
// Created by 杜建璋 on 2024/8/29.
//

#include "executor/share/boolean/and/AbstractAndShareExecutor.h"
#include "utils/Math.h"
#include "utils/Mpi.h"
#include "executor/bmt/RsaOtTripleGenerator.h"

AbstractAndShareExecutor::AbstractAndShareExecutor(bool x) {
    _x = x;
    _x1 = Math::rand32(0, 1);
    _x0 = _x1 xor _x;

    // triple
    _a0 = Math::rand32(0, 1);
    _b0 = Math::rand32(0, 1);
    _c0 = _a0 && _b0;
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
    if (Mpi::isCalculator()) {
        bool x0, y0, *self, *other;
        self = Mpi::rank() == 0 ? &x0 : &y0;
        other = Mpi::rank() == 0 ? &y0 : &x0;
        *self = _x0;
        if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
            Mpi::exchange(&_x1, other, _mpiTime);
        } else {
            Mpi::exchange(&_x1, other);
        }
        bool e0 = _a0 xor x0;
        bool f0 = _b0 xor y0;
        bool e1, f1;
        if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
            Mpi::exchange(&e0, &e1, _mpiTime);
            Mpi::exchange(&f0, &f1, _mpiTime);
        } else {
            Mpi::exchange(&e0, &e1);
            Mpi::exchange(&f0, &f1);
        }
        bool e = e0 xor e1;
        bool f = f0 xor f1;
        bool z0 = Mpi::rank() * e * f xor f * _a0 xor e * _b0 xor _c0;
        if (Mpi::size() == 2) {
            bool z1;
            if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
                Mpi::exchange(&z0, &z1, _mpiTime);
            } else {
                Mpi::exchange(&z0, &z1);
            }
            _result = z0 xor z1;
        } else {
            if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
                Mpi::sendTo(&z0, Mpi::TASK_PUBLISHER_RANK, _mpiTime);
            } else {
                Mpi::sendTo(&z0, Mpi::TASK_PUBLISHER_RANK);
            }
        }
    } else {
        bool z0, z1;
        if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
            Mpi::recvFrom(&z0, 0, _mpiTime);
            Mpi::recvFrom(&z1, 1, _mpiTime);
        } else {
            Mpi::recvFrom(&z0, 0);
            Mpi::recvFrom(&z1, 1);
        }
        _result = z0 xor z1;
    }
}
