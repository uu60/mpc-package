//
// Created by 杜建璋 on 2024/8/30.
//

#include "bmt/RsaOtTripleGenerator.h"
#include "ot/RsaOtExecutor.h"
#include "utils/Math.h"
#include "utils/Mpi.h"

template<typename T>
RsaOtTripleGenerator<T>::RsaOtTripleGenerator() = default;

template<typename T>
void RsaOtTripleGenerator<T>::generateRandomAB() {
    this->_ai = Math::ring(Math::rand64(), this->_l);
    this->_bi = Math::ring(Math::rand64(), this->_l);
}

template<typename T>
void RsaOtTripleGenerator<T>::computeU() {
    computeMix(0, this->_ui);
}

template<typename T>
void RsaOtTripleGenerator<T>::computeV() {
    computeMix(1, this->_vi);
}

template<typename T>
T RsaOtTripleGenerator<T>::corr(int i, T x) const {
    return Math::ring((this->_ai << i) - x, this->_l);
}

template<typename T>
void RsaOtTripleGenerator<T>::computeMix(int sender, T &mix) {
    bool isSender = Mpi::rank() == sender;
    T sum = 0;
    for (int i = 0; i < this->_l; i++) {
        T s0 = 0, s1 = 0;
        int choice = 0;
        if (isSender) {
            s0 = Math::ring(Math::rand64(), this->_l);
            s1 = corr(i, s0);
        } else {
            choice = (int) ((this->_bi >> i) & 1);
        }
        RsaOtExecutor r(sender, s0, s1, choice);
        r.logBenchmark(false);
        if (this->_benchmarkLevel == Executor<T>::BenchmarkLevel::DETAILED) {
            r.benchmark(Executor<T>::BenchmarkLevel::DETAILED);
        }
        r.execute(false);
        if (this->_benchmarkLevel == Executor<T>::BenchmarkLevel::DETAILED) {
            // add mpi time
            this->_mpiTime += r.mpiTime();
            _otMpiTime += r.mpiTime();
            _otRsaGenerationTime += r.rsaGenerationTime();
            _otRsaEncryptionTime += r.rsaEncryptionTime();
            _otRsaDecryptionTime += r.rsaDecryptionTime();
            _otEntireComputationTime += r.entireComputationTime();
        }
        if (isSender) {
            sum += s0;
        } else {
            T temp = r.result();
            if (choice == 0) {
                temp = -r.result();
            }
            sum += temp;
        }
    }
    mix = Math::ring(sum, this->_l);
}

template<typename T>
void RsaOtTripleGenerator<T>::computeC() {
    this->_ci = this->_ai * this->_bi + this->_ui + this->_vi;
}

template<typename T>
RsaOtTripleGenerator<T> *RsaOtTripleGenerator<T>::execute(bool dummy) {
    generateRandomAB();

    computeU();
    computeV();
    computeC();
    return this;
}

template<typename T>
int64_t RsaOtTripleGenerator<T>::otRsaGenerationTime() const {
    return _otRsaGenerationTime;
}

template<typename T>
int64_t RsaOtTripleGenerator<T>::otRsaEncryptionTime() const {
    return _otRsaEncryptionTime;
}

template<typename T>
int64_t RsaOtTripleGenerator<T>::otRsaDecryptionTime() const {
    return _otRsaDecryptionTime;
}

template<typename T>
int64_t RsaOtTripleGenerator<T>::otMpiTime() const {
    return _otMpiTime;
}

template<typename T>
int64_t RsaOtTripleGenerator<T>::otEntireComputationTime() const {
    return _otEntireComputationTime;
}

template<typename T>
std::string RsaOtTripleGenerator<T>::tag() const {
    return "[BMT Generator]";
}

template class RsaOtTripleGenerator<bool>;
template class RsaOtTripleGenerator<int8_t>;
template class RsaOtTripleGenerator<int16_t>;
template class RsaOtTripleGenerator<int32_t>;
template class RsaOtTripleGenerator<int64_t>;