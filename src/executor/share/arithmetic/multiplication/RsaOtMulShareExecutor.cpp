//
// Created by 杜建璋 on 2024/7/27.
//

#include "executor/share/arithmetic/multiplication/RsaOtMulShareExecutor.h"
#include "utils/MpiUtils.h"
#include "executor/bmt/MulTripleExecutor.h"

void RsaOtMulShareExecutor::obtainMultiplicationTriple() {
    MulTripleExecutor m(_l);
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

std::string RsaOtMulShareExecutor::tag() const {
    return "[RSA OT Multiplication Share]";
}
