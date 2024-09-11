//
// Created by 杜建璋 on 2024/9/6.
//

#include "executor/share/AbstractIntShareExecutor.h"
#include "utils/Mpi.h"
#include "utils/Math.h"

AbstractIntShareExecutor::AbstractIntShareExecutor() = default;

AbstractIntShareExecutor::AbstractIntShareExecutor(int64_t x, int64_t y, int l) {
    _l = Math::realL(l);
    bool detailed = _benchmarkLevel == BenchmarkLevel::DETAILED;
    // distribute data
    if (!Mpi::isCalculator()) {
        int64_t x1 = Math::ring(Math::rand64(), _l);
        int64_t x0 = Math::ring(x - x1, _l);
        int64_t y1 = Math::ring(Math::rand64(), _l);
        int64_t y0 = Math::ring(y - y1, _l);
        Mpi::sendTo(&x0, 0, _mpiTime, detailed);
        Mpi::sendTo(&y0, 0, _mpiTime, detailed);
        Mpi::sendTo(&x1, 1, _mpiTime, detailed);
        Mpi::sendTo(&y1, 1, _mpiTime, detailed);
    } else {
        // data
        Mpi::recvFrom(&_xi, Mpi::DATA_HOLDER_RANK, _mpiTime, detailed);
        Mpi::recvFrom(&_yi, Mpi::DATA_HOLDER_RANK, _mpiTime, detailed);
    }
}

AbstractIntShareExecutor::AbstractIntShareExecutor(int64_t xi, int64_t yi, int l, bool dummy) {
    _l = Math::realL(l);
    _xi = Math::ring(xi, _l);
    _yi = Math::ring(yi, _l);
}


