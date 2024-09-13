//
// Created by 杜建璋 on 2024/9/6.
//

#include "executor/share/IntShareExecutor.h"
#include "utils/Mpi.h"
#include "utils/Math.h"

IntShareExecutor::IntShareExecutor() = default;

IntShareExecutor::IntShareExecutor(int64_t x, int l) {
    _l = Math::normL(l);
    x = Math::ring(x, _l);
    bool detailed = _benchmarkLevel == BenchmarkLevel::DETAILED;
    // distribute operator
    if (Mpi::isDataHolder()) {
        int64_t x1 = Math::ring(Math::rand64(), _l);
        int64_t x0 = Math::ring(x - x1, _l);
        Mpi::sendTo(&x0, 0, _mpiTime, detailed);
        Mpi::sendTo(&x1, 1, _mpiTime, detailed);
    } else {
        Mpi::recvFrom(&_xi, Mpi::DATA_HOLDER_RANK, _mpiTime, detailed);
    }
}

IntShareExecutor::IntShareExecutor(int64_t x, int64_t y, int l) {
    _l = Math::normL(l);
    x = Math::ring(x, _l);
    y = Math::ring(y, _l);
    bool detailed = _benchmarkLevel == BenchmarkLevel::DETAILED;
    // distribute operator
    if (Mpi::isDataHolder()) {
        int64_t x1 = Math::ring(Math::rand64(), _l);
        int64_t x0 = Math::ring(x - x1, _l);
        int64_t y1 = Math::ring(Math::rand64(), _l);
        int64_t y0 = Math::ring(y - y1, _l);
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

IntShareExecutor::IntShareExecutor(int64_t xi, int64_t yi, int l, bool dummy) {
    _l = Math::normL(l);
    _xi = Math::ring(xi, _l);
    _yi = Math::ring(yi, _l);
}

IntShareExecutor *IntShareExecutor::execute(bool reconstruct) {
    return nullptr;
}

std::string IntShareExecutor::tag() const {
    return {};
}

int64_t IntShareExecutor::xi() const {
    return _xi;
}

IntShareExecutor *IntShareExecutor::zi(int64_t zi) {
    _zi = Math::ring(zi, _l);
    return this;
}

IntShareExecutor *IntShareExecutor::reconstruct() {
    bool detailed = _benchmarkLevel == BenchmarkLevel::DETAILED;
    if (Mpi::isCalculator()) {
        Mpi::sendTo(&_zi, Mpi::DATA_HOLDER_RANK, _mpiTime, detailed);
    } else {
        int64_t z0, z1;
        Mpi::recvFrom(&z0, 0, _mpiTime, detailed);
        Mpi::recvFrom(&z1, 1, _mpiTime, detailed);
        _result = Math::ring(z0 + z1, _l);
    }
    return this;
}


