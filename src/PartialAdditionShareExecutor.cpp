//
// Created by 杜建璋 on 2024/7/12.
//

#include "share/arithmetic/PartialAdditionShareExecutor.h"
#include "utils/MpiUtils.h"

PartialAdditionShareExecutor::PartialAdditionShareExecutor(int64_t xa, int64_t ya) {
    _xa = xa;
    _ya = ya;
}

void PartialAdditionShareExecutor::compute() {
    _za = _xa + _ya;
    MpiUtils::exchange(&_za, &_zb);
    _res = _za + _zb;
}
