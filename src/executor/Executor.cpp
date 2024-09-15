//
// Created by 杜建璋 on 2024/7/7.
//

#include "executor/Executor.h"

template<typename T>
void Executor<T>::finalize() {
    // do nothing by default
}

template<typename T>
T Executor<T>::result() const {
    return _result;
}

template<typename T>
Executor<T> *Executor<T>::benchmark(BenchmarkLevel lv) {
    _benchmarkLevel = lv;
    return this;
}

template<typename T>
int64_t Executor<T>::mpiTime() const {
    return _mpiTime;
}

template<typename T>
Executor<T> *Executor<T>::logBenchmark(bool isLogBenchmark) {
    _isLogBenchmark = isLogBenchmark;
    return this;
}

template<typename T>
int64_t Executor<T>::entireComputationTime() const {
    return _entireComputationTime;
}

template<typename T>
Executor<T> *Executor<T>::reconstruct() {
    throw std::runtime_error("This method cannot be called!");
}

template<typename T>
Executor<T> *Executor<T>::execute(bool reconstruct) {
    throw std::runtime_error("This method cannot be called!");
}

template<typename T>
std::string Executor<T>::tag() const {
    throw std::runtime_error("This method cannot be called!");
}

template class Executor<bool>;
template class Executor<int8_t>;
template class Executor<int16_t>;
template class Executor<int32_t>;
template class Executor<int64_t>;