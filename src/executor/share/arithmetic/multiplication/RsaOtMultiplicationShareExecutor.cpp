//
// Created by 杜建璋 on 2024/7/27.
//

#include "executor/share/arithmetic/multiplication/RsaOtMultiplicationShareExecutor.h"
#include "utils/Mpi.h"
#include "executor/bmt/RsaOtTripleGenerator.h"

void RsaOtMultiplicationShareExecutor::obtainMultiplicationTriple() {
    RsaOtTripleGenerator e(_l);
    e.setBenchmark(_benchmarkLevel);
    e.setLogBenchmark(false);
    e.compute();
    if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
        _mpiTime += e.getMpiTime();
    }
    _a0 = e.getA0();
    _b0 = e.getB0();
    _c0 = e.getC0();

    if (_benchmarkLevel == BenchmarkLevel::DETAILED && _isLogBenchmark) {
        Log::i(tag() + " OT RSA keys generation time: " + std::to_string(e.getOtRsaGenerationTime()) + " ms.");
        Log::i(tag() + " OT RSA encryption time: " + std::to_string(e.getOtRsaEncryptionTime()) + " ms.");
        Log::i(tag() + " OT RSA decryption time: " + std::to_string(e.getOtRsaDecryptionTime()) + " ms.");
        Log::i(tag() + " OT MPI transmission and synchronization time: " + std::to_string(e.getOtMpiTime()) + " ms.");
        Log::i(tag() + " OT total computation time: " + std::to_string(e.getOtEntireComputationTime()) + " ms.");
    }
}

std::string RsaOtMultiplicationShareExecutor::tag() const {
    return "[RSA OT Multiplication Share]";
}
