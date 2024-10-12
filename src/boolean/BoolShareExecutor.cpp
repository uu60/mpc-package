//
// Created by 杜建璋 on 2024/9/6.
//

#include "boolean/BoolShareExecutor.h"
#include "utils/Math.h"
#include "utils/Mpi.h"

BoolShareExecutor::BoolShareExecutor(bool x) {
    bool detailed = _benchmarkLevel == BenchmarkLevel::DETAILED;
    if (!Mpi::isServer()) {
        bool x1 = Math::rand32(0, 1);
        bool x0 = x1 ^ x;
        Mpi::send(&x0, 0, _mpiTime, detailed);
        Mpi::send(&x1, 1, _mpiTime, detailed);
    } else {
        // operator
        Mpi::recv(&_xi, Mpi::CLIENT_RANK, _mpiTime, detailed);
    }
}

BoolShareExecutor::BoolShareExecutor(bool x, bool y) {
    bool detailed = _benchmarkLevel == BenchmarkLevel::DETAILED;
    if (!Mpi::isServer()) {
        bool x1 = Math::rand32(0, 1);
        bool x0 = x1 ^ x;
        bool y1 = Math::rand32(0, 1);
        bool y0 = y1 ^ y;
        Mpi::send(&x0, 0, _mpiTime, detailed);
        Mpi::send(&y0, 0, _mpiTime, detailed);
        Mpi::send(&x1, 1, _mpiTime, detailed);
        Mpi::send(&y1, 1, _mpiTime, detailed);
    } else {
        // operator
        Mpi::recv(&_xi, Mpi::CLIENT_RANK, _mpiTime, detailed);
        Mpi::recv(&_yi, Mpi::CLIENT_RANK, _mpiTime, detailed);
    }
}

BoolShareExecutor::BoolShareExecutor(bool xi, bool yi, bool dummy) {
    _xi = xi;
    _yi = yi;
}

BoolShareExecutor *BoolShareExecutor::reconstruct() {
    bool detailed = _benchmarkLevel == Executor::BenchmarkLevel::DETAILED;
    if (Mpi::isServer()) {
        Mpi::send(&_zi, Mpi::CLIENT_RANK, _mpiTime, detailed);
    } else {
        bool z0, z1;
        Mpi::recv(&z0, 0, _mpiTime, detailed);
        Mpi::recv(&z1, 1, _mpiTime, detailed);
        _result = z0 ^ z1;
    }
    return this;
}

BoolShareExecutor *BoolShareExecutor::execute(bool reconstruct) {
    throw std::runtime_error("This method cannot be called!");
}

std::string BoolShareExecutor::tag() const {
    throw std::runtime_error("This method cannot be called!");
}

bool BoolShareExecutor::xi() const {
    return _xi;
}

BoolShareExecutor *BoolShareExecutor::zi(bool zi) {
    _zi = zi;
    return this;
}

bool BoolShareExecutor::zi() {
    return _zi;
}
