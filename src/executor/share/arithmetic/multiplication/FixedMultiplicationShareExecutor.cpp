//
// Created by 杜建璋 on 2024/7/27.
//

#include "executor/share/arithmetic/multiplication/FixedMultiplicationShareExecutor.h"
#include "executor/bmt/FixedTripleGenerator.h"
#include "utils/Mpi.h"

void FixedMultiplicationShareExecutor::obtainMultiplicationTriple() {
    FixedTripleGenerator e(_l);
    e.benchmark(_benchmarkLevel);
    e.logBenchmark(false);
    e.compute();

    _a0 = e.a0();
    _b0 = e.b0();
    _c0 = e.c0();
}

std::string FixedMultiplicationShareExecutor::tag() const {
    return "[Fixed Multiplication Share]";
}

