//
// Created by 杜建璋 on 2024/7/13.
//

#include "executor/arithmetic/CompleteAdditionExecutor.h"
#include "utils/Utils.h"

void CompleteAdditionExecutor::compute() {
    Executor::exchange(&xb, &ya);
    za = xa + ya;
    Executor::exchange(&za, &zb);
    res = za + zb;
}

void CompleteAdditionExecutor::init() {
    obtainX();
    xb = Utils::randomInt();
    xa = x - xb;
}

