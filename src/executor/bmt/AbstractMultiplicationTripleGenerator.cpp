//
// Created by 杜建璋 on 2024/8/30.
//

#include "executor/bmt/AbstractMultiplicationTripleGenerator.h"

int64_t AbstractMultiplicationTripleGenerator::ai() const {
    return _ai;
}

int64_t AbstractMultiplicationTripleGenerator::bi() const {
    return _bi;
}

int64_t AbstractMultiplicationTripleGenerator::ci() const {
    return _ci;
}

AbstractMultiplicationTripleGenerator *AbstractMultiplicationTripleGenerator::reconstruct() {
    return this;
}
