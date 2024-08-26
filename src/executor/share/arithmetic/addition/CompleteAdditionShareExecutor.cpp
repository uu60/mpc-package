//
// Created by 杜建璋 on 2024/7/13.
//

#include "executor/share/arithmetic/addition/CompleteAdditionShareExecutor.h"
#include "utils/MathUtils.h"
#include "utils/MpiUtils.h"
#include <limits>

CompleteAdditionShareExecutor::CompleteAdditionShareExecutor(int64_t x) {
    _x = x;
    _x1 = MathUtils::rand64();
    _x0 = _x - _x1;
}

void CompleteAdditionShareExecutor::compute() {
    MpiUtils::exchange(&_x1, &_y0);
    _z0 = _x0 + _y0;
    MpiUtils::exchange(&_z0, &_z1);
    _res = _z0 + _z1;
}

