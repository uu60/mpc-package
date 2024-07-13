//
// Created by 杜建璋 on 2024/7/13.
//

#include "executor/arithmetic/MultiplicationExecutor.h"
#include "utils/Utils.h"

void MultiplicationExecutor::compute() {
    int xi, yi, *self, *other;
    self = mpiRank == 0 ? &xi : &yi;
    other = mpiRank == 0 ? &yi : &xi;

    *self = xa;
    Executor::exchange(&xb, other);
    int ea = xi - aa;
    int fa = yi - ba;
    int eb, fb;
    Executor::exchange(&ea, &eb);
    Executor::exchange(&fa, &fb);
    int e = ea + eb;
    int f = fa + fb;
    int za = mpiRank * e * f + f * aa + e * ba + ca;
    int zb;
    Executor::exchange(&za, &zb);
    res = za + zb;
}

void MultiplicationExecutor::init() {
    // data
    obtainX();
    xb = Utils::randomInt();
    xa = x - xb;
    // MT
    obtainMultiplicationTriple();
}

void MultiplicationExecutor::obtainMultiplicationTriple() {
    // temporarily fixed
    int a[] = {6, 9};
    int b[] = {12, 8};
    int c[] = {125, 175};
    aa = a[mpiRank];
    ba = b[mpiRank];
    ca = c[mpiRank];
}
