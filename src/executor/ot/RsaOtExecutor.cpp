//
// Created by 杜建璋 on 2024/7/15.
//

#include "executor/ot/RsaOtExecutor.h"
#include "utils/Mpi.h"
#include "utils/Math.h"
#include "utils/Crypto.h"

RsaOtExecutor::RsaOtExecutor(int sender, int64_t m0, int64_t m1, int i)
        : RsaOtExecutor(2048, sender, m0, m1, i) {
}

RsaOtExecutor::RsaOtExecutor(int bits, int sender, int64_t m0, int64_t m1, int i) {
    _bits = bits;
    _isSender = sender == Mpi::rank();
    if (_isSender) {
        _m0 = m0;
        _m1 = m1;
    } else {
        _i = i;
    }
}

RsaOtExecutor* RsaOtExecutor::execute(bool dummy) {
    int64_t start, end;
    if (_benchmarkLevel >= BenchmarkLevel::GENERAL) {
        start = System::currentTimeMillis();
    }
    // preparation
    generateAndShareRandoms();
    generateAndShareRsaKeys();

    // process
    process();
    if (_benchmarkLevel >= BenchmarkLevel::GENERAL) {
        end = System::currentTimeMillis();
        if (_isLogBenchmark) {
            Log::i(tag() + " Entire computation time: " + std::to_string(end - start) + "ms.");
            Log::i(tag() + " MPI transmission and synchronization time: " + std::to_string(_mpiTime) + " ms.");
        }
        _entireComputationTime = end - start;
    }
    return this;
}

void RsaOtExecutor::generateAndShareRsaKeys() {
    if (_isSender) {
        int64_t start, end;
        if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
            start = System::currentTimeMillis();
        }
        Crypto::generateRsaKeys(_bits, _pub, _pri);
        if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
            end = System::currentTimeMillis();
            if (_isLogBenchmark) {
                Log::i(tag() + " RSA keys generation time: " + std::to_string(end - start) + " ms.");
            }
            _rsaGenerationTime = end - start;
            Mpi::sendC(&_pub, _mpiTime);
        } else {
            Mpi::sendC(&_pub);
        }
        return;
    }
    // receiver
    if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
        Mpi::recvC(&_pub, _mpiTime);
    } else {
        Mpi::recvC(&_pub);
    }
}

void RsaOtExecutor::generateAndShareRandoms() {
    // 11 for PKCS#1 v1.5 padding
    int maxLen = (_bits >> 3) - 11;
    if (_isSender) {
        _rand0 = Math::rand0b(1, maxLen);
        _rand1 = Math::rand0b(1, maxLen);
        if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
            Mpi::sendC(&_rand0, _mpiTime);
            Mpi::sendC(&_rand1, _mpiTime);
        } else {
            Mpi::sendC(&_rand0);
            Mpi::sendC(&_rand1);
        }
    } else {
        _randK = Math::rand0b(1, maxLen);
        if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
            Mpi::recvC(&_rand0, _mpiTime);
            Mpi::recvC(&_rand1, _mpiTime);
        } else {
            Mpi::recvC(&_rand0);
            Mpi::recvC(&_rand1);
        }
    }
}

void RsaOtExecutor::process() {
    if (!_isSender) {
        int64_t start, end;
        if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
            start = System::currentTimeMillis();
        }
        std::string ek = Crypto::rsaEncrypt(_randK, _pub);
        if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
            end = System::currentTimeMillis();
            if (_isLogBenchmark) {
                Log::i(tag() + " RSA encryption time: " + std::to_string(end - start) + " ms.");
            }
            _rsaEncryptionTime = end - start;
        }
        std::string sumStr = Math::add(ek, _i == 0 ? _rand0 : _rand1);
        if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
            Mpi::sendC(&sumStr, _mpiTime);
        } else {
            Mpi::sendC(&sumStr);
        }

        std::string m0, m1;
        if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
            Mpi::recvC(&m0);
            Mpi::recvC(&m1);
        } else {
            Mpi::recvC(&m0, _mpiTime);
            Mpi::recvC(&m1, _mpiTime);
        }

        _result = std::stoll(Math::minus(_i == 0 ? m0 : m1, _randK));
    } else {
        std::string sumStr;
        if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
            Mpi::recvC(&sumStr, _mpiTime);
        } else {
            Mpi::recvC(&sumStr);
        }
        int64_t start, end;
        if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
            start = System::currentTimeMillis();
        }
        std::string k0 = Crypto::rsaDecrypt(
                Math::minus(sumStr, _rand0), _pri
        );
        std::string k1 = Crypto::rsaDecrypt(
                Math::minus(sumStr, _rand1), _pri
        );
        if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
            end = System::currentTimeMillis();
            if (_isLogBenchmark) {
                Log::i(tag() + " RSA decryption time: " + std::to_string(end - start) + " ms.");
            }
            _rsaDecryptionTime = end - start;
        }
        std::string m0 = Math::add(std::to_string(_m0), k0);
        std::string m1 = Math::add(std::to_string(_m1), k1);
        if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
            Mpi::sendC(&m0, _mpiTime);
            Mpi::sendC(&m1, _mpiTime);
        } else {
            Mpi::sendC(&m0);
            Mpi::sendC(&m1);
        }
    }
}

int64_t RsaOtExecutor::rsaGenerationTime() const {
    return _rsaGenerationTime;
}

int64_t RsaOtExecutor::rsaEncryptionTime() const {
    return _rsaEncryptionTime;
}

int64_t RsaOtExecutor::rsaDecryptionTime() const {
    return _rsaDecryptionTime;
}

std::string RsaOtExecutor::tag() const {
    return "[RSA OT]";
}

RsaOtExecutor *RsaOtExecutor::reconstruct() {
    return this;
}
