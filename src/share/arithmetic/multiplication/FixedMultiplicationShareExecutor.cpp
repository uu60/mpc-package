//
// Created by 杜建璋 on 2024/7/27.
//

#include "share/arithmetic/multiplication/FixedMultiplicationShareExecutor.h"
#include "bmt/FixedTripleGenerator.h"
#include "utils/Mpi.h"

template<typename T>
FixedMultiplicationShareExecutor<T>::FixedMultiplicationShareExecutor(T x, T y) : AbstractMultiplicationShareExecutor<T>(x, y) {}

template<typename T>
FixedMultiplicationShareExecutor<T>::FixedMultiplicationShareExecutor(T x, T y, bool dummy)
        : AbstractMultiplicationShareExecutor<T>(x, y, dummy) {}

template<typename T>
void FixedMultiplicationShareExecutor<T>::obtainMultiplicationTriple() {
    FixedTripleGenerator<T> e;
    e.benchmark(this->_benchmarkLevel);
    e.logBenchmark(false);
    e.execute(false);

    this->_ai = e.ai();
    this->_bi = e.bi();
    this->_ci = e.ci();
}

template<typename T>
std::string FixedMultiplicationShareExecutor<T>::tag() const {
    return "[Fixed Multiplication Share]";
}

template class FixedMultiplicationShareExecutor<bool>;
template class FixedMultiplicationShareExecutor<int8_t>;
template class FixedMultiplicationShareExecutor<int16_t>;
template class FixedMultiplicationShareExecutor<int32_t>;
template class FixedMultiplicationShareExecutor<int64_t>;


