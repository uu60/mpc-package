//
// Created by 杜建璋 on 2024/7/6.
//

#include "Test.h"

void Test::obtainX1() {

    if (mpiRank == 0) {
        x1 = 100;
    } else {
        x1 = 50;
    }
}

void Test::obtainY1() {
    if (mpiRank == 0) {
        y1 = 200;
    } else {
        y1 = 150;
    }
}
