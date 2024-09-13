//
// Created by 杜建璋 on 2024/8/30.
//

#include "executor/share/boolean/and/FixedAndShareExecutor.h"
#include "executor/bmt/FixedTripleGenerator.h"

FixedAndShareExecutor::FixedAndShareExecutor(bool x, bool y) : AbstractAndShareExecutor(x, y) {}

FixedAndShareExecutor::FixedAndShareExecutor(bool x, bool y, bool dummy) : AbstractAndShareExecutor(x, y, dummy) {}

void FixedAndShareExecutor::obtainMultiplicationTriple() {
    FixedTripleGenerator e(1);
    e.benchmark(_benchmarkLevel);
    e.logBenchmark(false);
    e.execute(false);

    _ai = e.getAi();
    _bi = e.getBi();
    _ci = e.getCi();
}

std::string FixedAndShareExecutor::tag() const {
    return "[Fixed And Boolean Share]";
}
