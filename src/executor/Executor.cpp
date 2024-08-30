//
// Created by 杜建璋 on 2024/7/7.
//

#include "executor/Executor.h"

void Executor::finalize() {
    // do nothing by default
}

int64_t Executor::result() const {
    return _res;
}

void Executor::benchmark(BenchmarkLevel lv) {
    _benchmarkLevel = lv;
}

int64_t Executor::mpiTime() const {
    return _mpiTime;
}

void Executor::logBenchmark(bool isLogBenchmark) {
    _isLogBenchmark = isLogBenchmark;
}

int64_t Executor::entireComputationTime() const {
    return _entireComputationTime;
}

