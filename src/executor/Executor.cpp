//
// Created by 杜建璋 on 2024/7/7.
//

#include "executor/Executor.h"

void Executor::finalize() {
    // do nothing by default
}

int64_t Executor::getResult() const {
    return _res;
}

void Executor::setBenchmark(BenchmarkLevel lv) {
    _benchmarkLevel = lv;
}

int64_t Executor::getMpiTime() const {
    return _mpiTime;
}

void Executor::setLogBenchmark(bool isLogBenchmark) {
    _isLogBenchmark = isLogBenchmark;
}

int64_t Executor::getEntireComputationTime() const {
    return _entireComputationTime;
}

