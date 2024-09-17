//
// Created by 杜建璋 on 2024/9/2.
//

#include "share/comparison/ComparisonExecutor.h"
#include "utils/Mpi.h"

template<typename T>
ComparisonExecutor<T>::ComparisonExecutor(T x, T y) : IntShareExecutor<T>(x, y) {}

template<typename T>
ComparisonExecutor<T>::ComparisonExecutor(T xi, T yi, bool dummy) : IntShareExecutor<T>(xi, yi, dummy) {}

template<typename T>
ComparisonExecutor<T> *ComparisonExecutor<T>::execute(bool reconstruct) {
    bool detailed = this->_benchmarkLevel == Executor<T>::BenchmarkLevel::DETAILED;
    if (Mpi::isCalculator()) {
        T zi = this->_xi - this->_yi;
        if (reconstruct) {
            Mpi::sendTo(&zi, Mpi::DATA_HOLDER_RANK, this->_mpiTime, detailed);
        }
    } else {
        if (reconstruct) {
            T z0, z1;
            Mpi::recvFrom(&z0, 0, this->_mpiTime, detailed);
            Mpi::recvFrom(&z1, 1, this->_mpiTime, detailed);
            T z = z0 + z1;
            this->_result = (z > 0 ? 1 : ((z == 0) ? 0 : -1));
        }
    }
    return this;
}

