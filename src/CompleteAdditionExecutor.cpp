//
// Created by 杜建璋 on 2024/7/13.
//

#include "share/arithmetic/CompleteAdditionExecutor.h"
#include "utils/MathUtils.h"
#include "utils/MpiUtils.h"

void CompleteAdditionExecutor::compute() {
    MpiUtils::exchange(&xb, &ya);
    za = xa + ya;
    MpiUtils::exchange(&za, &zb);
    res = za + zb;
}

void CompleteAdditionExecutor::init(int x0) {
    x = x0;
    xb = MathUtils::randomInt();
    xa = x - xb;
    inited();
}

