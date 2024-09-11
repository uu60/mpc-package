//
// Created by 杜建璋 on 2024/7/13.
//

#include "executor/share/arithmetic/addition/AdditionShareExecutor.h"
#include "utils/Math.h"
#include "utils/Mpi.h"
#include "utils/System.h"
#include <limits>

AdditionShareExecutor::AdditionShareExecutor(int64_t x, int64_t y, int l) : AbstractIntShareExecutor(x, y, l) {}

AdditionShareExecutor::AdditionShareExecutor(int64_t xi, int64_t yi, int l, bool dummy) : AbstractIntShareExecutor(xi, yi, l, dummy) {}

AdditionShareExecutor::AdditionShareExecutor(std::vector<int64_t> &xis, int l) {
    mode = Mode::ARRAY;
    _l = l;
    for (int64_t xi: xis) {
        _xi += xi;
        Math::ring(_xi, _l);
    }
}

AdditionShareExecutor *AdditionShareExecutor::execute() {
    bool detailed = _benchmarkLevel == BenchmarkLevel::DETAILED;
    switch (mode) {
        case Mode::DUAL: {
            int64_t start;
            if (_benchmarkLevel >= BenchmarkLevel::GENERAL) {
                start = System::currentTimeMillis();
            }
            if (Mpi::isCalculator()) {
                int64_t zi = _xi + _yi;
                Mpi::sendTo(&zi, Mpi::DATA_HOLDER_RANK, _mpiTime, detailed);
            } else {
                int64_t z0, z1;
                Mpi::recvFrom(&z0, 0, _mpiTime, detailed);
                Mpi::recvFrom(&z1, 1, _mpiTime, detailed);
                _result = z0 + z1;
            }
            if (_benchmarkLevel >= BenchmarkLevel::GENERAL) {
                _entireComputationTime = System::currentTimeMillis() - start;
                if (_isLogBenchmark) {
                    if (detailed) {
                        Log::i(tag(),
                               "Mpi synchronization and transmission time: " + std::to_string(_mpiTime) + " ms.");
                    }
                    Log::i(tag(), "Entire computation time: " + std::to_string(_entireComputationTime) + " ms.");
                }
            }
            break;
        }
        case Mode::ARRAY: {
            if (Mpi::isCalculator()) {
                Mpi::sendTo(&_xi, Mpi::DATA_HOLDER_RANK, _mpiTime, detailed);
            } else {
                int64_t z0, z1;
                Mpi::recvFrom(&z0, 0, _mpiTime, detailed);
                Mpi::recvFrom(&z1, 1, _mpiTime, detailed);
                _result = Math::ring(z0 + z1, 32);
            }
            break;
        }
    }

    return this;
}

std::string AdditionShareExecutor::tag() const {
    return "[Addition Share]";
}

