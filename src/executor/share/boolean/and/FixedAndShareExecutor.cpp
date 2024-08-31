//
// Created by 杜建璋 on 2024/8/30.
//

#include "executor/share/boolean/and/FixedAndShareExecutor.h"
#include "executor/bmt/FixedTripleGenerator.h"

void FixedAndShareExecutor::obtainMultiplicationTriple() {
    FixedTripleGenerator e(1);
    e.benchmark(_benchmarkLevel);
    e.logBenchmark(false);
    e.compute();

    _a0 = e.a0();
    _b0 = e.b0();
    _c0 = e.c0();
}

std::string FixedAndShareExecutor::tag() const {
    return "[Fixed And Boolean Share]";
}
