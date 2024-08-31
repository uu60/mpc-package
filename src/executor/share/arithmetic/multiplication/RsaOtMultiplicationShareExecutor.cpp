//
// Created by 杜建璋 on 2024/7/27.
//

#include "executor/share/arithmetic/multiplication/RsaOtMultiplicationShareExecutor.h"
#include "utils/Mpi.h"
#include "executor/bmt/RsaOtTripleGenerator.h"

void RsaOtMulShareExecutor::obtainMultiplicationTriple() {
    RsaOtTripleGenerator e(_l);
    e.benchmark(_benchmarkLevel);
    e.logBenchmark(false);
    e.compute();
    _a0 = e.a0();
    _b0 = e.b0();
    _c0 = e.c0();

    if (_benchmarkLevel == BenchmarkLevel::DETAILED && _isLogBenchmark) {
        Log::i(tag() + " OT RSA keys generation time: " + std::to_string(e.otRsaGenerationTime()) + " ms.");
        Log::i(tag() + " OT RSA encryption time: " + std::to_string(e.otRsaEncryptionTime()) + " ms.");
        Log::i(tag() + " OT RSA decryption time: " + std::to_string(e.otRsaDecryptionTime()) + " ms.");
        Log::i(tag() + " OT MPI transmission and synchronization time: " + std::to_string(e.otMpiTime()) + " ms.");
        Log::i(tag() + " OT total computation time: " + std::to_string(e.otEntireComputationTime()) + " ms.");
    }
}

std::string RsaOtMulShareExecutor::tag() const {
    return "[RSA OT Multiplication Share]";
}
