//
// Created by 杜建璋 on 2024/7/13.
//

#include "executor/share/arithmetic/addition/AdditionShareExecutor.h"
#include "utils/Mpi.h"
#include "utils/System.h"
#include <limits>

template<typename T>
AdditionShareExecutor<T>::AdditionShareExecutor(T x, T y) : IntShareExecutor<T>(x, y) {}

template<typename T>
AdditionShareExecutor<T>::AdditionShareExecutor(T xi, T yi, bool dummy) : IntShareExecutor<T>(xi, yi, dummy) {}

template<typename T>
AdditionShareExecutor<T>::AdditionShareExecutor(std::vector<T> &xis) {
    mode = Mode::ARRAY;
    for (T xi: xis) {
        this->_zi += xi;
    }
    this->_zi;
}

template<typename T>
AdditionShareExecutor<T> *AdditionShareExecutor<T>::execute(bool reconstruct) {
    bool detailed = this->_benchmarkLevel == Executor<T>::BenchmarkLevel::DETAILED;
    switch (mode) {
        case Mode::DUAL: {
            T start;
            if (this->_benchmarkLevel >= Executor<T>::BenchmarkLevel::GENERAL) {
                start = System::currentTimeMillis();
            }
            if (Mpi::isCalculator()) {
                this->_zi = this->_xi + this->_yi;
                this->_result = this->_zi;
            }
            if (reconstruct) {
                this->reconstruct();
            }
            if (this->_benchmarkLevel >= Executor<T>::BenchmarkLevel::GENERAL) {
                this->_entireComputationTime = System::currentTimeMillis() - start;
                if (this->_isLogBenchmark) {
                    if (detailed) {
                        Log::i(tag(),
                               "Mpi synchronization and transmission time: " + std::to_string(this->_mpiTime) + " ms.");
                    }
                    Log::i(tag(), "Entire computation time: " + std::to_string(this->_entireComputationTime) + " ms.");
                }
            }
            break;
        }
        case Mode::ARRAY: {
            if (reconstruct) {
                this->reconstruct();
            }
            break;
        }
    }

    return this;
}

template<typename T>
std::string AdditionShareExecutor<T>::tag() const {
    return "[Addition Share]";
}

template class AdditionShareExecutor<bool>;
template class AdditionShareExecutor<int8_t>;
template class AdditionShareExecutor<int16_t>;
template class AdditionShareExecutor<int32_t>;
template class AdditionShareExecutor<int64_t>;