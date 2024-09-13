//
// Created by 杜建璋 on 2024/7/7.
//

#include "executor/Executor.h"

void Executor::finalize() {
    // do nothing by default
}

int64_t Executor::result() const {
    return _result;
}

Executor* Executor::benchmark(BenchmarkLevel lv) {
    _benchmarkLevel = lv;
    return this;
}

int64_t Executor::mpiTime() const {
    return _mpiTime;
}

Executor* Executor::logBenchmark(bool isLogBenchmark) {
    _isLogBenchmark = isLogBenchmark;
    return this;
}

int64_t Executor::entireComputationTime() const {
    return _entireComputationTime;
}

Executor *Executor::reconstruct() {
    throw std::runtime_error("This method cannot be called!");
}

Executor *Executor::execute(bool reconstruct) {
    throw std::runtime_error("This method cannot be called!");
}

std::string Executor::tag() const {
    throw std::runtime_error("This method cannot be called!");
}

