//
// Created by 杜建璋 on 2024/7/13.
//

#include "share/arithmetic/MultiplicationShareExecutor.h"
#include "utils/MpiUtils.h"
#include "utils/MathUtils.h"
#include <vector>

MultiplicationShareExecutor::MultiplicationShareExecutor(int64_t x, int l) {
    // data
    _x = x;
    _xb = MathUtils::rand32();
    _xa = _x - _xb;

    _l = l;
    // MT
    obtainMultiplicationTriple();
}

void MultiplicationShareExecutor::compute() {
    int64_t xi, yi, *self, *other;
    self = MpiUtils::getMpiRank() == 0 ? &xi : &yi;
    other = MpiUtils::getMpiRank() == 0 ? &yi : &xi;

    *self = _xa;
    MpiUtils::exchange(&_xb, other);
    int64_t ea = xi - _aa;
    int64_t fa = yi - _ba;
    int64_t eb, fb;
    MpiUtils::exchange(&ea, &eb);
    MpiUtils::exchange(&fa, &fb);
    int64_t e = ea + eb;
    int64_t f = fa + fb;
    int64_t za = MpiUtils::getMpiRank() * e * f + f * _aa + e * _ba + _ca;
    int64_t zb;
    MpiUtils::exchange(&za, &zb);
    _res = za + zb;
}

void MultiplicationShareExecutor::obtainMultiplicationTriple() {
    // temporarily fixed
    int a[] = {6, 9};
    int b[] = {12, 8};
    int c[] = {125, 175};
    _aa = a[MpiUtils::getMpiRank()];
    _ba = b[MpiUtils::getMpiRank()];
    _ca = c[MpiUtils::getMpiRank()];
}