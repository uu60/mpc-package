//
// Created by 杜建璋 on 2024/7/27.
//

#include "executor/share/arithmetic/multiplication/RsaOtMultiplicationShareExecutor.h"
#include "utils/Mpi.h"
#include "executor/bmt/RsaOtTripleGenerator.h"

RsaOtMultiplicationShareExecutor::RsaOtMultiplicationShareExecutor(int64_t x, int64_t y, int l): AbstractMultiplicationShareExecutor(x, y, l) {}

void RsaOtMultiplicationShareExecutor::obtainMultiplicationTriple() {
    RsaOtTripleGenerator e(_l);
    e.setBenchmark(_benchmarkLevel);
    e.setLogBenchmark(false);
    e.compute();
    if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
        _mpiTime += e.getMpiTime();
    }
    _ai = e.getAi();
    _bi = e.getBi();
    _ci = e.getCi();

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
