//
// Created by 杜建璋 on 2024/9/6.
//

#include "executor/share/boolean/AbstractBoolShareExecutor.h"
#include "utils/Math.h"
#include "utils/Mpi.h"

AbstractBoolShareExecutor::AbstractBoolShareExecutor(int64_t x, int64_t y) {
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
