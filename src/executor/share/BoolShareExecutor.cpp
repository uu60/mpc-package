//
// Created by 杜建璋 on 2024/9/6.
//

#include "executor/share/BoolShareExecutor.h"
#include "utils/Math.h"
#include "utils/Mpi.h"

BoolShareExecutor::BoolShareExecutor(int64_t x, int64_t y) {
    bool detailed = _benchmarkLevel == BenchmarkLevel::DETAILED;
    if (!Mpi::isCalculator()) {
        bool x1 = Math::rand32(0, 1);
        bool x0 = x1 xor x;
        bool y1 = Math::rand32(0, 1);
        bool y0 = y1 xor y;
        Mpi::sendTo(&x0, 0, _mpiTime, detailed);
        Mpi::sendTo(&y0, 0, _mpiTime, detailed);
        Mpi::sendTo(&x1, 1, _mpiTime, detailed);
        Mpi::sendTo(&y1, 1, _mpiTime, detailed);
    } else {
        // operator
        Mpi::recvFrom(&_xi, Mpi::DATA_HOLDER_RANK, _mpiTime, detailed);
        Mpi::recvFrom(&_yi, Mpi::DATA_HOLDER_RANK, _mpiTime, detailed);
    }
}

BoolShareExecutor::BoolShareExecutor(int64_t xi, int64_t yi, bool dummy) {
    _xi = xi;
    _yi = yi;
}

Executor *BoolShareExecutor::reconstruct() {
    bool detailed = _benchmarkLevel == Executor::BenchmarkLevel::DETAILED;
    if (Mpi::isCalculator()) {
        Mpi::sendTo(&_zi, Mpi::DATA_HOLDER_RANK, _mpiTime, detailed);
    } else {
        bool z0, z1;
        Mpi::recvFrom(&z0, 0, _mpiTime, detailed);
        Mpi::recvFrom(&z1, 1, _mpiTime, detailed);
        _result = z0 xor z1;
    }
    return this;
}

Executor *BoolShareExecutor::execute(bool reconstruct) {
    throw std::runtime_error("This method cannot be called!");
}

std::string BoolShareExecutor::tag() const {
    throw std::runtime_error("This method cannot be called!");
}
