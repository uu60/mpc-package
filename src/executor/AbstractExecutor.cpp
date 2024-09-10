//
// Created by 杜建璋 on 2024/7/7.
//

#include "executor/AbstractExecutor.h"

void AbstractExecutor::finalize() {
    // do nothing by default
}

int64_t AbstractExecutor::result() const {
    return _result;
}

AbstractExecutor* AbstractExecutor::benchmark(BenchmarkLevel lv) {
    _benchmarkLevel = lv;
    return this;
}

int64_t AbstractExecutor::mpiTime() const {
    return _mpiTime;
}

AbstractExecutor* AbstractExecutor::logBenchmark(bool isLogBenchmark) {
    _isLogBenchmark = isLogBenchmark;
    return this;
}

int64_t AbstractExecutor::entireComputationTime() const {
    return _entireComputationTime;
}

