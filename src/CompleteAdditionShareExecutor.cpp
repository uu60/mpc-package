//
// Created by 杜建璋 on 2024/7/13.
//

#include "share/arithmetic/CompleteAdditionShareExecutor.h"
#include "utils/MathUtils.h"
#include "utils/MpiUtils.h"

CompleteAdditionShareExecutor::CompleteAdditionShareExecutor(int64_t x) {
    _x = x;
    _xb = MathUtils::rand32();
    _xa = _x - _xb;
}

void CompleteAdditionShareExecutor::compute() {
    MpiUtils::exchange(&_xb, &_ya);
    _za = _xa + _ya;
    MpiUtils::exchange(&_za, &_zb);
    _res = _za + _zb;
}

