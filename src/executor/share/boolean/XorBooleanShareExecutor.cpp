//
// Created by 杜建璋 on 2024/8/29.
//

#include "executor/share/boolean/XorBooleanShareExecutor.h"
#include "utils/MathUtils.h"
#include "utils/MpiUtils.h"

XorBooleanShareExecutor::XorBooleanShareExecutor(bool x) {
    _x = x;
    _x1 = MathUtils::rand32(0, 1);
    _x0 = _x0 xor _x;
}

void XorBooleanShareExecutor::compute() {
    MpiUtils::exchange(&_x1, &_y0);
    _z0 = _x0 xor _y0;
    MpiUtils::exchange(&_z0, &_z1);
    _res = _z0 xor _z1;
}
