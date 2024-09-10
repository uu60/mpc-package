//
// Created by 杜建璋 on 2024/9/2.
//

#include "executor/share/comparison/ComparisonExecutor.h"
#include "utils/Mpi.h"

ComparisonExecutor::ComparisonExecutor(int64_t x, int64_t y) : AbstractIntegerShareExecutor(x, y) {}

ComparisonExecutor::ComparisonExecutor(int64_t xi, int64_t yi, bool dummy) : AbstractIntegerShareExecutor(xi, yi, dummy) {}

ComparisonExecutor* ComparisonExecutor::execute() {
    bool bm = _benchmarkLevel == BenchmarkLevel::DETAILED;
    if (Mpi::isCalculator()) {
        int64_t zi = _xi - _yi;
        Mpi::sendTo(&zi, Mpi::TASK_PUBLISHER_RANK, _mpiTime, bm);
    } else {
        int64_t z0, z1;
        Mpi::recvFrom(&z0, 0, _mpiTime, bm);
        Mpi::recvFrom(&z1, 1, _mpiTime, bm);
        int64_t z = z0 + z1;
        _result = (z > 0 ? 1 : ((z == 0) ? 0 : -1));
    }
    return this;
}

