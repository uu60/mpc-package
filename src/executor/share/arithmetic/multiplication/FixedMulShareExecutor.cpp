//
// Created by 杜建璋 on 2024/7/27.
//

#include "executor/share/arithmetic/multiplication/FixedMulShareExecutor.h"
#include "executor/bmt/FixedTripleExecutor.h"
#include "utils/MpiUtils.h"

void FixedMulShareExecutor::obtainMultiplicationTriple() {
    FixedTripleExecutor e(_l);
    e.benchmark(_benchmarkLevel);
    e.logBenchmark(false);
    e.compute();

    _a0 = e.a0();
    _b0 = e.b0();
    _c0 = e.c0();
}

std::string FixedMulShareExecutor::tag() const {
    return "[Fixed Multiplication Share]";
}

