//
// Created by 杜建璋 on 2024/8/30.
//

#include "executor/share/boolean/and/FixedAndShareExecutor.h"
#include "executor/bmt/FixedTripleGenerator.h"

void FixedAndShareExecutor::obtainMultiplicationTriple() {
    FixedTripleGenerator e(1);
    e.setBenchmark(_benchmarkLevel);
    e.setLogBenchmark(false);
    e.compute();

    _a0 = e.getA0();
    _b0 = e.getB0();
    _c0 = e.getC0();
}

std::string FixedAndShareExecutor::tag() const {
    return "[Fixed And Boolean Share]";
}
