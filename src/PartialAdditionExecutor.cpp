//
// Created by 杜建璋 on 2024/7/12.
//

#include "share/arithmetic/PartialAdditionExecutor.h"
#include "utils/MathUtils.h"
#include "utils/MpiUtils.h"

void PartialAdditionExecutor::compute() {
    _za = _xa + _ya;
    MpiUtils::exchange(&_za, &_zb);
    _res = _za + _zb;
}

void PartialAdditionExecutor::init(int64_t xa, int64_t ya) {
    _xa = xa;
    _ya = ya;
    inited();
}
