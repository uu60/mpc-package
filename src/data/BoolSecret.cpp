//
// Created by 杜建璋 on 2024/9/13.
//

#include "data/BoolSecret.h"
#include "executor/share/BoolShareExecutor.h"

BoolSecret::BoolSecret(bool x) {
    _data = x;
}

BoolSecret BoolSecret::share() const {
    return BoolSecret(BoolShareExecutor(_data).xi());
}

BoolSecret BoolSecret::xor_(bool yi) const {
    return BoolSecret(_data xor yi);
}

BoolSecret BoolSecret::xor_(BoolSecret yi) const {
    return xor_(yi.get());
}

BoolSecret BoolSecret::and_(bool yi) const {
    return BoolSecret(_data and yi);
}

BoolSecret BoolSecret::and_(BoolSecret yi) const {
    return and_(yi.get());
}

BoolSecret BoolSecret::reconstruct() const {
    return BoolSecret(BoolShareExecutor(false).zi(_data)->reconstruct()->result());
}

bool BoolSecret::get() const {
    return _data;
}

BoolSecret BoolSecret::share(bool x) {
    return BoolSecret(BoolShareExecutor(x).xi());
}

BoolSecret BoolSecret::xor_(bool xi, bool yi) {
    return BoolSecret(xi xor yi);
}

BoolSecret BoolSecret::xor_(BoolSecret xi, BoolSecret yi) {
    return xor_(xi.get(), yi.get());
}

BoolSecret BoolSecret::and_(bool xi, bool yi) {
    return BoolSecret(xi and yi);
}

BoolSecret BoolSecret::and_(BoolSecret xi, BoolSecret yi) {
    return and_(xi.get(), yi.get());
}


















