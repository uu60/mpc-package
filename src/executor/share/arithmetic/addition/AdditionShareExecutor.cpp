//
// Created by 杜建璋 on 2024/7/13.
//

#include "executor/share/arithmetic/addition/AdditionShareExecutor.h"
#include "utils/Math.h"
#include "utils/Mpi.h"
#include <limits>

AdditionShareExecutor::AdditionShareExecutor(int64_t x) {
    _x = x;
    _x1 = Math::rand64();
    _x0 = _x - _x1;
}

void AdditionShareExecutor::compute() {
    int64_t y0, z0, z1;
    if (Mpi::size() == 2) {
        Mpi::exchange(&_x1, &y0);
        z0 = _x0 + y0;
        Mpi::exchange(&z0, &z1);
        _result = z0 + z1;
    } else {
        if (Mpi::isCalculator()) {
            Mpi::exchange(&_x1, &y0);
            z0 = _x0 + y0;
            Mpi::sendTo(&z0, Mpi::TASK_PUBLISHER_RANK);
        } else {
            Mpi::recvFrom(&z0, 0);
            Mpi::recvFrom(&z1, 1);
            _result = z0 + z1;
        }
    }
}

std::string AdditionShareExecutor::tag() const {
    return "[Addition Share]";
}

