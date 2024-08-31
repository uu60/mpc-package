//
// Created by 杜建璋 on 2024/8/29.
//

#include "executor/share/boolean/xor/XorShareExecutor.h"
#include "utils/Math.h"
#include "utils/Mpi.h"

XorShareExecutor::XorShareExecutor(bool x) {
    _x = x;
    _x1 = Math::rand32(0, 1);
    _x0 = _x1 xor _x;
}

void XorShareExecutor::compute() {
    Mpi::exchange(&_x1, &_y0);
    _z0 = _x0 xor _y0;
    Mpi::exchange(&_z0, &_z1);
    _result = _z0 xor _z1;
}

std::string XorShareExecutor::tag() const {
    return "[XOR Boolean Share]";
}
