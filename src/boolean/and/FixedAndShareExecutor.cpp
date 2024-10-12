//
// Created by 杜建璋 on 2024/8/30.
//

#include "boolean/and/FixedAndShareExecutor.h"
#include "bmt/FixedTripleGenerator.h"

FixedAndShareExecutor::FixedAndShareExecutor(bool x, bool y) : AbstractAndShareExecutor(x, y) {}

FixedAndShareExecutor::FixedAndShareExecutor(bool x, bool y, bool dummy) : AbstractAndShareExecutor(x, y, dummy) {}

void FixedAndShareExecutor::obtainMultiplicationTriple() {
    FixedTripleGenerator<bool> e;
    e.benchmark(_benchmarkLevel);
    e.logBenchmark(false);
    e.execute(false);

    _ai = e.ai();
    _bi = e.bi();
    _ci = e.ci();
}

std::string FixedAndShareExecutor::tag() const {
    return "[Fixed And Boolean Share]";
}
