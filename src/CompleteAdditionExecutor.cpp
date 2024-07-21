//
// Created by 杜建璋 on 2024/7/13.
//

#include "share/arithmetic/CompleteAdditionExecutor.h"
#include "utils/MathUtils.h"
#include "utils/MpiUtils.h"

void CompleteAdditionExecutor::compute() {
    MpiUtils::exchange(&_xb, &_ya);
    _za = _xa + _ya;
    MpiUtils::exchange(&_za, &_zb);
    _res = _za + _zb;
}

void CompleteAdditionExecutor::init(int64_t x) {
    _x = x;
    _xb = MathUtils::rand32();
    _xa = _x - _xb;
    inited();
}

