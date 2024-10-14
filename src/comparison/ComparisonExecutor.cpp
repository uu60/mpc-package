//
// Created by 杜建璋 on 2024/9/2.
//

#include "comparison/ComparisonExecutor.h"
#include "boolean/and/RsaOtAndShareExecutor.h"
#include "utils/Mpi.h"
#include "utils/Math.h"
#include <vector>

template<typename T>
ComparisonExecutor<T>::ComparisonExecutor(T x, T y) : IntShareExecutor<T>(x, y) {
    this->_zi = this->_xi - this->_yi;
}

template<typename T>
ComparisonExecutor<T>::ComparisonExecutor(T xi, T yi, bool dummy) : IntShareExecutor<T>(xi, yi, dummy) {
    this->_zi = this->_xi - this->_yi;
}

template<typename T>
ComparisonExecutor<T> *ComparisonExecutor<T>::execute(bool reconstruct) {
    if (Mpi::isServer()) {
        this->convertZToBoolShare();
        this->_sign = this->_cvtZ < 0;
    }
    if (reconstruct) {
        this->reconstruct();
    }
    return this;
}

template<typename T>
ComparisonExecutor<T> *ComparisonExecutor<T>::convertZToBoolShare() {
    // bitwise separate zi
    // zi is xor shared into zi_i and zi_o
//    Log::i("zi = " + std::to_string(this->_zi));
    T zi_i = Math::rand64();
    T zi_o = zi_i ^ this->_zi;
    bool carry_i = false;
//    std::vector<int> ais, bis;

    for (int i = 0; i < this->_l; i++) {
        bool ai, ao, bi, bo;
        bool *self_i = Mpi::rank() == 0 ? &ai : &bi;
        bool *self_o = Mpi::rank() == 0 ? &ao : &bo;
        bool *other_i = Mpi::rank() == 0 ? &bi : &ai;
        *self_i = (zi_i >> i) & 1;
        *self_o = (zi_o >> i) & 1;
        Mpi::sexch(self_o, other_i, this->_mpiTime);
        this->_cvtZ += ((ai ^ bi) ^ carry_i) << i;

        // Compute carry_i
        bool generate_i = RsaOtAndShareExecutor(ai, bi, false).execute(false)->zi();
        bool propagate_i = ai ^ bi;
        bool tempCarry_i = RsaOtAndShareExecutor(propagate_i, carry_i, false).execute(false)->zi();
        bool sum_i = generate_i ^ tempCarry_i;
        bool and_i = RsaOtAndShareExecutor(generate_i, tempCarry_i, false).execute(false)->zi();

        carry_i = sum_i ^ and_i;
    }

    return this;
}

template<typename T>
ComparisonExecutor<T> *ComparisonExecutor<T>::reconstruct() {
    bool detailed = this->_benchmarkLevel == Executor<T>::BenchmarkLevel::DETAILED;
    if (Mpi::isServer()) {
        Mpi::send(&this->_sign, Mpi::CLIENT_RANK, this->_mpiTime, detailed);
    } else {
        bool sign0, sign1;
        Mpi::recv(&sign0, 0, this->_mpiTime, detailed);
        Mpi::recv(&sign1, 1, this->_mpiTime, detailed);
        this->_result = sign0 ^ sign1;
    }
    return this;
}

template<typename T>
std::string ComparisonExecutor<T>::tag() const {
    return "[Comparison]";
}

template class ComparisonExecutor<int8_t>;
template class ComparisonExecutor<int16_t>;
template class ComparisonExecutor<int32_t>;
template class ComparisonExecutor<int64_t>;