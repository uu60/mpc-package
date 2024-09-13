//
// Created by 杜建璋 on 2024/7/27.
//

#include "executor/share/arithmetic/multiplication/FixedMultiplicationShareExecutor.h"
#include "executor/bmt/FixedTripleGenerator.h"
#include "utils/Mpi.h"

FixedMultiplicationShareExecutor::FixedMultiplicationShareExecutor(int64_t x, int64_t y, int l) : AbstractMultiplicationShareExecutor(x, y, l) {}

FixedMultiplicationShareExecutor::FixedMultiplicationShareExecutor(int64_t x, int64_t y, int l, bool dummy)
        : AbstractMultiplicationShareExecutor(x, y, l, dummy) {}

void FixedMultiplicationShareExecutor::obtainMultiplicationTriple() {
    FixedTripleGenerator e(_l);
    e.benchmark(_benchmarkLevel);
    e.logBenchmark(false);
    e.execute(false);

    _ai = e.ai();
    _bi = e.bi();
    _ci = e.ci();
}

std::string FixedMultiplicationShareExecutor::tag() const {
    return "[Fixed Multiplication Share]";
}



