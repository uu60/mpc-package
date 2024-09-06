//
// Created by 杜建璋 on 2024/7/27.
//

#include "executor/share/arithmetic/multiplication/FixedMultiplicationShareExecutor.h"
#include "executor/bmt/FixedTripleGenerator.h"
#include "utils/Mpi.h"

void FixedMultiplicationShareExecutor::obtainMultiplicationTriple() {
    FixedTripleGenerator e(_l);
    e.setBenchmark(_benchmarkLevel);
    e.setLogBenchmark(false);
    e.compute();

    _ai = e.getAi();
    _bi = e.getBi();
    _ci = e.getCi();
}

std::string FixedMultiplicationShareExecutor::tag() const {
    return "[Fixed Multiplication Share]";
}

