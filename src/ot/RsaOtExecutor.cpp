//
// Created by 杜建璋 on 2024/7/15.
//

#include "ot/RsaOtExecutor.h"
#include "utils/Mpi.h"
#include "utils/Math.h"
#include "utils/Crypto.h"

template<typename T>
RsaOtExecutor<T>::RsaOtExecutor(int sender, T m0, T m1, int i)
        : RsaOtExecutor(2048, sender, m0, m1, i) {
}

template<typename T>
RsaOtExecutor<T>::RsaOtExecutor(int bits, int sender, T m0, T m1, int i) {
    _bits = bits;
    _isSender = sender == Mpi::rank();
    if (_isSender) {
        _m0 = m0;
        _m1 = m1;
    } else {
        _i = i;
    }
}

template<typename T>
RsaOtExecutor<T> *RsaOtExecutor<T>::execute(bool dummy) {
    int64_t start, end;
    if (this->_benchmarkLevel >= Executor<T>::BenchmarkLevel::GENERAL) {
        start = System::currentTimeMillis();
    }
    // preparation
    generateAndShareRandoms();
    generateAndShareRsaKeys();

    // process
    process();
    if (this->_benchmarkLevel >= Executor<T>::BenchmarkLevel::GENERAL) {
        end = System::currentTimeMillis();
        if (this->_isLogBenchmark) {
            Log::i(tag() + " Entire computation time: " + std::to_string(end - start) + "ms.");
            Log::i(tag() + " MPI transmission and synchronization time: " + std::to_string(this->_mpiTime) + " ms.");
        }
        this->_entireComputationTime = end - start;
    }
    return this;
}

template<typename T>
void RsaOtExecutor<T>::generateAndShareRsaKeys() {
    if (_isSender) {
        int64_t start, end;
        if (this->_benchmarkLevel == Executor<T>::BenchmarkLevel::DETAILED) {
            start = System::currentTimeMillis();
        }
        Crypto::generateRsaKeys(_bits, _pub, _pri);
        if (this->_benchmarkLevel == Executor<T>::BenchmarkLevel::DETAILED) {
            end = System::currentTimeMillis();
            if (this->_isLogBenchmark) {
                Log::i(tag() + " RSA keys generation time: " + std::to_string(end - start) + " ms.");
            }
            _rsaGenerationTime = end - start;
            Mpi::sendC(&_pub, this->_mpiTime);
        } else {
            Mpi::sendC(&_pub);
        }
        return;
    }
    // receiver
    if (this->_benchmarkLevel == Executor<T>::BenchmarkLevel::DETAILED) {
        Mpi::recvC(&_pub, this->_mpiTime);
    } else {
        Mpi::recvC(&_pub);
    }
}

template<typename T>
void RsaOtExecutor<T>::generateAndShareRandoms() {
    // 11 for PKCS#1 v1.5 padding
    int maxLen = (_bits >> 3) - 11;
    if (_isSender) {
        _rand0 = Math::rand0b(1, maxLen);
        _rand1 = Math::rand0b(1, maxLen);
        if (this->_benchmarkLevel == Executor<T>::BenchmarkLevel::DETAILED) {
            Mpi::sendC(&_rand0, this->_mpiTime);
            Mpi::sendC(&_rand1, this->_mpiTime);
        } else {
            Mpi::sendC(&_rand0);
            Mpi::sendC(&_rand1);
        }
    } else {
        _randK = Math::rand0b(1, maxLen);
        if (this->_benchmarkLevel == Executor<T>::BenchmarkLevel::DETAILED) {
            Mpi::recvC(&_rand0, this->_mpiTime);
            Mpi::recvC(&_rand1, this->_mpiTime);
        } else {
            Mpi::recvC(&_rand0);
            Mpi::recvC(&_rand1);
        }
    }
}

template<typename T>
void RsaOtExecutor<T>::process() {
    if (!_isSender) {
        int64_t start, end;
        if (this->_benchmarkLevel == Executor<T>::BenchmarkLevel::DETAILED) {
            start = System::currentTimeMillis();
        }
        std::string ek = Crypto::rsaEncrypt(_randK, _pub);
        if (this->_benchmarkLevel == Executor<T>::BenchmarkLevel::DETAILED) {
            end = System::currentTimeMillis();
            if (this->_isLogBenchmark) {
                Log::i(tag() + " RSA encryption time: " + std::to_string(end - start) + " ms.");
            }
            _rsaEncryptionTime = end - start;
        }
        std::string sumStr = Math::add(ek, _i == 0 ? _rand0 : _rand1);
        if (this->_benchmarkLevel == Executor<T>::BenchmarkLevel::DETAILED) {
            Mpi::sendC(&sumStr, this->_mpiTime);
        } else {
            Mpi::sendC(&sumStr);
        }

        std::string m0, m1;
        if (this->_benchmarkLevel == Executor<T>::BenchmarkLevel::DETAILED) {
            Mpi::recvC(&m0);
            Mpi::recvC(&m1);
        } else {
            Mpi::recvC(&m0, this->_mpiTime);
            Mpi::recvC(&m1, this->_mpiTime);
        }

        this->_result = std::stoll(Math::minus(_i == 0 ? m0 : m1, _randK));
    } else {
        std::string sumStr;
        if (this->_benchmarkLevel == Executor<T>::BenchmarkLevel::DETAILED) {
            Mpi::recvC(&sumStr, this->_mpiTime);
        } else {
            Mpi::recvC(&sumStr);
        }
        int64_t start, end;
        if (this->_benchmarkLevel == Executor<T>::BenchmarkLevel::DETAILED) {
            start = System::currentTimeMillis();
        }
        std::string k0 = Crypto::rsaDecrypt(
                Math::minus(sumStr, _rand0), _pri
        );
        std::string k1 = Crypto::rsaDecrypt(
                Math::minus(sumStr, _rand1), _pri
        );
        if (this->_benchmarkLevel == Executor<T>::BenchmarkLevel::DETAILED) {
            end = System::currentTimeMillis();
            if (this->_isLogBenchmark) {
                Log::i(tag() + " RSA decryption time: " + std::to_string(end - start) + " ms.");
            }
            _rsaDecryptionTime = end - start;
        }
        std::string m0 = Math::add(std::to_string(_m0), k0);
        std::string m1 = Math::add(std::to_string(_m1), k1);
        if (this->_benchmarkLevel == Executor<T>::BenchmarkLevel::DETAILED) {
            Mpi::sendC(&m0, this->_mpiTime);
            Mpi::sendC(&m1, this->_mpiTime);
        } else {
            Mpi::sendC(&m0);
            Mpi::sendC(&m1);
        }
    }
}

template<typename T>
int64_t RsaOtExecutor<T>::rsaGenerationTime() const {
    return _rsaGenerationTime;
}

template<typename T>
int64_t RsaOtExecutor<T>::rsaEncryptionTime() const {
    return _rsaEncryptionTime;
}

template<typename T>
int64_t RsaOtExecutor<T>::rsaDecryptionTime() const {
    return _rsaDecryptionTime;
}

template<typename T>
std::string RsaOtExecutor<T>::tag() const {
    return "[RSA OT]";
}

template<typename T>
RsaOtExecutor<T> *RsaOtExecutor<T>::reconstruct() {
    return this;
}

template class RsaOtExecutor<bool>;
template class RsaOtExecutor<int8_t>;
template class RsaOtExecutor<int16_t>;
template class RsaOtExecutor<int32_t>;
template class RsaOtExecutor<int64_t>;