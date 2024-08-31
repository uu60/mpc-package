//
// Created by 杜建璋 on 2024/7/7.
//

#include "executor/AbstractExecutor.h"

void AbstractExecutor::finalize() {
    // do nothing by default
}

int64_t AbstractExecutor::getResult() const {
    return _result;
}

void AbstractExecutor::setBenchmark(BenchmarkLevel lv) {
    _benchmarkLevel = lv;
}

int64_t AbstractExecutor::getMpiTime() const {
    return _mpiTime;
}

void AbstractExecutor::setLogBenchmark(bool isLogBenchmark) {
    _isLogBenchmark = isLogBenchmark;
}

int64_t AbstractExecutor::getEntireComputationTime() const {
    return _entireComputationTime;
}

