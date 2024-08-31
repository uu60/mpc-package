//
// Created by 杜建璋 on 2024/8/30.
//

#include "executor/share/boolean/and/RsaOtAndShareExecutor.h"

void RsaOtAndShareExecutor::obtainMultiplicationTriple() {
    RsaOtTripleGenerator m(1);
    m.benchmark(_benchmarkLevel);
    m.compute();
    _a0 = m.a0();
    _b0 = m.b0();
    _c0 = m.c0();

    if (_benchmarkLevel == BenchmarkLevel::DETAILED && _isLogBenchmark) {
        Log::i(tag() + " OT RSA keys generation time: " + std::to_string(m.otRsaGenerationTime()) + " ms.");
        Log::i(tag() + " OT RSA encryption time: " + std::to_string(m.otRsaEncryptionTime()) + " ms.");
        Log::i(tag() + " OT RSA decryption time: " + std::to_string(m.otRsaDecryptionTime()) + " ms.");
        Log::i(tag() + " OT MPI transmission and synchronization time: " + std::to_string(m.otMpiTime()) + " ms.");
        Log::i(tag() + " OT total computation time: " + std::to_string(m.otEntireComputationTime()) + " ms.");
    }
}

std::string RsaOtAndShareExecutor::tag() const {
    return "[RSA OT And Share]";
}