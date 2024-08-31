//
// Created by 杜建璋 on 2024/7/12.
//

#include "executor/share/arithmetic/addition/PartialAdditionShareExecutor.h"
#include "utils/Mpi.h"

PartialAdditionShareExecutor::PartialAdditionShareExecutor(int64_t x0, int64_t y0) {
    _x0 = x0;
    _y0 = y0;
}

void PartialAdditionShareExecutor::compute() {
    _z0 = _x0 + _y0;
    Mpi::exchange(&_z0, &_z1);
    _res = _z0 + _z1;
}

std::string PartialAdditionShareExecutor::tag() const {
    return "[Partial Addition Share]";
}
