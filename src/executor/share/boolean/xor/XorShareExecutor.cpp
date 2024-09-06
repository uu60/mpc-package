//
// Created by 杜建璋 on 2024/8/29.
//

#include "executor/share/boolean/xor/XorShareExecutor.h"
#include "utils/Mpi.h"

XorShareExecutor::XorShareExecutor(bool x, bool y) : AbstractBoolShareExecutor(x, y) {}

void XorShareExecutor::compute() {
    bool bm = _benchmarkLevel == BenchmarkLevel::DETAILED;
    if (Mpi::isCalculator()) {
        bool zi = _xi xor _yi;
        Mpi::sendTo(&zi, Mpi::TASK_PUBLISHER_RANK, _mpiTime, bm);
    } else {
        bool z0, z1;
        Mpi::recvFrom(&z0, 0, _mpiTime, bm);
        Mpi::recvFrom(&z1, 1, _mpiTime, bm);
        _result = z0 xor z1;
    }
}

std::string XorShareExecutor::tag() const {
    return "[XOR Boolean Share]";
}
