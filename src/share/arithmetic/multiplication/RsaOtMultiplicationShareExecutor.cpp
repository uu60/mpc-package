//
// Created by 杜建璋 on 2024/7/27.
//

#include "share/arithmetic/multiplication/RsaOtMultiplicationShareExecutor.h"
#include "utils/Mpi.h"
#include "bmt/RsaOtTripleGenerator.h"

template<typename T>
RsaOtMultiplicationShareExecutor<T>::RsaOtMultiplicationShareExecutor(T x, T y): AbstractMultiplicationShareExecutor<T>(x, y) {}

template<typename T>
RsaOtMultiplicationShareExecutor<T>::RsaOtMultiplicationShareExecutor(T x, T y, bool dummy)
        : AbstractMultiplicationShareExecutor<T>(x, y, dummy) {}

template<typename T>
void RsaOtMultiplicationShareExecutor<T>::obtainMultiplicationTriple() {
    RsaOtTripleGenerator<T> e;
    e.benchmark(this->_benchmarkLevel)->logBenchmark(false)->execute(false);
    if (this->_benchmarkLevel == Executor<T>::BenchmarkLevel::DETAILED) {
        this->_mpiTime += e.mpiTime();
    }
    this->_ai = e.ai();
    this->_bi = e.bi();
    this->_ci = e.ci();

    if (this->_benchmarkLevel == Executor<T>::BenchmarkLevel::DETAILED && this->_isLogBenchmark) {
        Log::i(tag() + " OT RSA keys generation time: " + std::to_string(e.otRsaGenerationTime()) + " ms.");
        Log::i(tag() + " OT RSA encryption time: " + std::to_string(e.otRsaEncryptionTime()) + " ms.");
        Log::i(tag() + " OT RSA decryption time: " + std::to_string(e.otRsaDecryptionTime()) + " ms.");
        Log::i(tag() + " OT MPI transmission and synchronization time: " + std::to_string(e.otMpiTime()) + " ms.");
        Log::i(tag() + " OT total computation time: " + std::to_string(e.otEntireComputationTime()) + " ms.");
    }
}

template<typename T>
std::string RsaOtMultiplicationShareExecutor<T>::tag() const {
    return "[RSA OT Multiplication Share]";
}

template class RsaOtMultiplicationShareExecutor<bool>;
template class RsaOtMultiplicationShareExecutor<int8_t>;
template class RsaOtMultiplicationShareExecutor<int16_t>;
template class RsaOtMultiplicationShareExecutor<int32_t>;
template class RsaOtMultiplicationShareExecutor<int64_t>;