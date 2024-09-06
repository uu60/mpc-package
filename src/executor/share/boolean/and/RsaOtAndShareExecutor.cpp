//
// Created by 杜建璋 on 2024/8/30.
//

#include "executor/share/boolean/and/RsaOtAndShareExecutor.h"

RsaOtAndShareExecutor::RsaOtAndShareExecutor(bool x, bool y) : AbstractAndShareExecutor(x, y) {}

RsaOtAndShareExecutor::RsaOtAndShareExecutor(bool x, bool y, bool dummy) : AbstractAndShareExecutor(x, y, dummy) {}

void RsaOtAndShareExecutor::obtainMultiplicationTriple() {
    RsaOtTripleGenerator m(1);
    m.setBenchmark(_benchmarkLevel);
    m.compute();
    if (_benchmarkLevel == BenchmarkLevel::DETAILED) {

    }
    _ai = m.getAi();
    _bi = m.getBi();
    _ci = m.getCi();

    if (_benchmarkLevel == BenchmarkLevel::DETAILED && _isLogBenchmark) {
        Log::i(tag() + " OT RSA keys generation time: " + std::to_string(m.getOtRsaGenerationTime()) + " ms.");
        Log::i(tag() + " OT RSA encryption time: " + std::to_string(m.getOtRsaEncryptionTime()) + " ms.");
        Log::i(tag() + " OT RSA decryption time: " + std::to_string(m.getOtRsaDecryptionTime()) + " ms.");
        Log::i(tag() + " OT MPI transmission and synchronization time: " + std::to_string(m.getOtMpiTime()) + " ms.");
        Log::i(tag() + " OT total computation time: " + std::to_string(m.getOtEntireComputationTime()) + " ms.");
    }
}

std::string RsaOtAndShareExecutor::tag() const {
    return "[RSA OT And Share]";
}

