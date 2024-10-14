//
// Created by 杜建璋 on 2024/8/30.
//

#include "boolean/and/RsaOtAndShareExecutor.h"

RsaOtAndShareExecutor::RsaOtAndShareExecutor(bool x, bool y) : AbstractAndShareExecutor(x, y) {}

RsaOtAndShareExecutor::RsaOtAndShareExecutor(bool xi, bool yi, bool dummy) : AbstractAndShareExecutor(xi, yi, dummy) {}

void RsaOtAndShareExecutor::obtainMultiplicationTriple() {
    RsaOtTripleGenerator<bool> e;
    e.benchmark(_benchmarkLevel);
    e.execute(false);
    if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
        this->_mpiTime += e.mpiTime();
    }
    _ai = e.ai();
    _bi = e.bi();
    _ci = e.ci();

    if (_benchmarkLevel == BenchmarkLevel::DETAILED && _isLogBenchmark) {
        Log::i(tag() + " OT RSA keys generation time: " + std::to_string(e.otRsaGenerationTime()) + " ms.");
        Log::i(tag() + " OT RSA encryption time: " + std::to_string(e.otRsaEncryptionTime()) + " ms.");
        Log::i(tag() + " OT RSA decryption time: " + std::to_string(e.otRsaDecryptionTime()) + " ms.");
        Log::i(tag() + " OT MPI transmission and synchronization time: " + std::to_string(e.otMpiTime()) + " ms.");
        Log::i(tag() + " OT total computation time: " + std::to_string(e.otEntireComputationTime()) + " ms.");
    }
}

std::string RsaOtAndShareExecutor::tag() const {
    return "[RSA OT And Share]";
}

