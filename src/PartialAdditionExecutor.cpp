//
// Created by 杜建璋 on 2024/7/12.
//

#include "executor/arithmetic/PartialAdditionExecutor.h"
#include "utils/Utils.h"

void PartialAdditionExecutor::init() {
    obtainXA();
    obtainYA();
}

void PartialAdditionExecutor::compute() {
    za = xa + ya;
    Executor::exchange(&za, &zb);
    res = za + zb;
}
