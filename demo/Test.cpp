//
// Created by 杜建璋 on 2024/7/6.
//

#include "Test.h"

void Test::obtainXA() {
    xa = mpiRank == 0 ? 100 : 50;
}

void Test::obtainYA() {
    ya = mpiRank == 0 ? 200 : 150;
}
