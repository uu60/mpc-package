//
// Created by 杜建璋 on 2024/7/27.
//

#include "executor/share/arithmetic/multiplication/FixedMultiplicationShareExecutor.h"
#include "executor/bmt/FixedTripleGenerator.h"
#include "utils/Mpi.h"

FixedMultiplicationShareExecutor::FixedMultiplicationShareExecutor(int64_t x, int64_t y, int l) : AbstractMultiplicationShareExecutor(x, y, l) {}

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



