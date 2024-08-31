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
    Mpi::exchange(&_x1, &_y0);
    _z0 = _x0 + _y0;
    Mpi::exchange(&_z0, &_z1);
    _result = _z0 + _z1;
}

std::string AdditionShareExecutor::tag() const {
    return "[Addition Share]";
}

