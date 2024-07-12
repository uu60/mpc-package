//
// Created by 杜建璋 on 2024/7/12.
//

#include "executor/arithmetic/AdditiveExecutor.h"
#include "utils/Utils.h"

void AdditiveExecutor::init() {
    obtainX1();
    obtainY1();
}

void AdditiveExecutor::compute() {
    z1 = x1 + y1;
    Utils::exchangeData(&z1, &z2, mpiRank);
    res = z1 + z2;
}
