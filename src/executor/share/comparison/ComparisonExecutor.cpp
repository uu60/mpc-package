//
// Created by 杜建璋 on 2024/9/2.
//

#include "executor/share/comparison/ComparisonExecutor.h"
#include "utils/Mpi.h"

ComparisonExecutor::ComparisonExecutor(int64_t x, int64_t y, int l) : AbstractIntShareExecutor(x, y, l) {}

ComparisonExecutor::ComparisonExecutor(int64_t xi, int64_t yi, int l, bool dummy) : AbstractIntShareExecutor(xi, yi, l, dummy) {}

ComparisonExecutor* ComparisonExecutor::execute() {
    bool detailed = _benchmarkLevel == BenchmarkLevel::DETAILED;
    if (Mpi::isCalculator()) {
        int64_t zi = _xi - _yi;
        Mpi::sendTo(&zi, Mpi::DATA_HOLDER_RANK, _mpiTime, detailed);
    } else {
        int64_t z0, z1;
        Mpi::recvFrom(&z0, 0, _mpiTime, detailed);
        Mpi::recvFrom(&z1, 1, _mpiTime, detailed);
        int64_t z = z0 + z1;
        _result = (z > 0 ? 1 : ((z == 0) ? 0 : -1));
    }
    return this;
}

