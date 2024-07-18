//
// Created by 杜建璋 on 2024/7/13.
//

#include "share/arithmetic/MultiplicationExecutor.h"
#include "utils/MpiUtils.h"
#include "utils/MathUtils.h"
#include <vector>

void MultiplicationExecutor::compute() {
    int xi, yi, *self, *other;
    self = MpiUtils::getMpiRank() == 0 ? &xi : &yi;
    other = MpiUtils::getMpiRank() == 0 ? &yi : &xi;

    *self = xa;
    MpiUtils::exchange(&xb, other);
    int ea = xi - aa;
    int fa = yi - ba;
    int eb, fb;
    MpiUtils::exchange(&ea, &eb);
    MpiUtils::exchange(&fa, &fb);
    int e = ea + eb;
    int f = fa + fb;
    int za = MpiUtils::getMpiRank() * e * f + f * aa + e * ba + ca;
    int zb;
    MpiUtils::exchange(&za, &zb);
    res = za + zb;
}

void MultiplicationExecutor::init(int x0, int l0) {
    // data
    x = x0;
    xb = MathUtils::randomInt();
    xa = x - xb;

    l = l0;
    // MT
    obtainMultiplicationTriple();
    // inited
    inited();
}

void MultiplicationExecutor::obtainMultiplicationTriple() {
    // temporarily fixed
    int a[] = {6, 9};
    int b[] = {12, 8};
    int c[] = {125, 175};
    aa = a[MpiUtils::getMpiRank()];
    ba = b[MpiUtils::getMpiRank()];
    ca = c[MpiUtils::getMpiRank()];
}