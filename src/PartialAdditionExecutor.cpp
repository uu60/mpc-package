//
// Created by 杜建璋 on 2024/7/12.
//

#include "share/arithmetic/PartialAdditionExecutor.h"
#include "utils/MathUtils.h"
#include "utils/MpiUtils.h"

void PartialAdditionExecutor::compute() {
    za = xa + ya;
    MpiUtils::exchange(&za, &zb);
    res = za + zb;
}

void PartialAdditionExecutor::init(int xa0, int ya0) {
    xa = xa0;
    ya = ya0;
    inited();
}
