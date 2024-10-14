//
// Created by 杜建璋 on 2024/9/6.
//

#include "arithmetic/IntShareExecutor.h"
#include "boolean/and/RsaOtAndShareExecutor.h"
#include "utils/Mpi.h"
#include "utils/Math.h"
#include <vector>

template<typename T>
IntShareExecutor<T>::IntShareExecutor() = default;

template<typename T>
IntShareExecutor<T>::IntShareExecutor(T x) {
    bool detailed = this->_benchmarkLevel == Executor<T>::BenchmarkLevel::DETAILED;
    // distribute operator
    if (Mpi::isClient()) {
        T x1 = Math::rand64();
        T x0 = x - x1;
        Mpi::send(&x0, 0, this->_mpiTime, detailed);
        Mpi::send(&x1, 1, this->_mpiTime, detailed);
    } else {
        Mpi::recv(&_xi, Mpi::CLIENT_RANK, this->_mpiTime, detailed);
    }
}

template<typename T>
IntShareExecutor<T>::IntShareExecutor(T x, T y) {
    bool detailed = this->_benchmarkLevel == Executor<T>::BenchmarkLevel::DETAILED;
    // distribute operator
    if (Mpi::isClient()) {
        T x1 = Math::rand64();
        T x0 = x - x1;
        T y1 = Math::rand64();
        T y0 = y - y1;
        Mpi::send(&x0, 0, this->_mpiTime, detailed);
        Mpi::send(&y0, 0, this->_mpiTime, detailed);
        Mpi::send(&x1, 1, this->_mpiTime, detailed);
        Mpi::send(&y1, 1, this->_mpiTime, detailed);
    } else {
        // operator
        Mpi::recv(&_xi, Mpi::CLIENT_RANK, this->_mpiTime, detailed);
        Mpi::recv(&_yi, Mpi::CLIENT_RANK, this->_mpiTime, detailed);
    }
}

template<typename T>
IntShareExecutor<T>::IntShareExecutor(T xi, T yi, bool dummy) {
    _xi = xi;
    _yi = yi;
}

template<typename T>
IntShareExecutor<T> *IntShareExecutor<T>::execute(bool reconstruct) {
    throw std::runtime_error("This method cannot be called!");
}

template<typename T>
std::string IntShareExecutor<T>::tag() const {
    throw std::runtime_error("This method cannot be called!");
}

template<typename T>
T IntShareExecutor<T>::xi() const {
    return _xi;
}

template<typename T>
IntShareExecutor<T> *IntShareExecutor<T>::zi(T zi) {
    _zi = zi;
    return this;
}

template<typename T>
IntShareExecutor<T> *IntShareExecutor<T>::reconstruct() {
    bool detailed = this->_benchmarkLevel == Executor<T>::BenchmarkLevel::DETAILED;
    if (Mpi::isServer()) {
        Mpi::send(&_zi, Mpi::CLIENT_RANK, this->_mpiTime, detailed);
    } else {
        T z0, z1;
        Mpi::recv(&z0, 0, this->_mpiTime, detailed);
        Mpi::recv(&z1, 1, this->_mpiTime, detailed);
        this->_result = z0 + z1;
    }
    return this;
}

template<typename T>
IntShareExecutor<T> *IntShareExecutor<T>::convertToBool() {
    // bitwise separate zi
    // zi is xor shared into zi_i and zi_o
    T zi_i = Math::rand64();
    T zi_o = zi_i ^ this->_zi;
    this->_zi = 0;
    bool carry_i = false;

    for (int i = 0; i < this->_l; i++) {
        bool ai, ao, bi, bo;
        bool *self_i = Mpi::rank() == 0 ? &ai : &bi;
        bool *self_o = Mpi::rank() == 0 ? &ao : &bo;
        bool *other_i = Mpi::rank() == 0 ? &bi : &ai;
        *self_i = (zi_i >> i) & 1;
        *self_o = (zi_o >> i) & 1;
        Mpi::sexch(self_o, other_i, this->_mpiTime);
        this->_zi += ((ai ^ bi) ^ carry_i) << i;

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
T IntShareExecutor<T>::zi() {
    return _zi;
}

template
class IntShareExecutor<int8_t>;

template
class IntShareExecutor<int16_t>;

template
class IntShareExecutor<int32_t>;

template
class IntShareExecutor<int64_t>;
