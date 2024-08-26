//
// Created by 杜建璋 on 2024/7/27.
//

#include "executor/share/arithmetic/multiplication/RsaOtMultiplicationShareExecutor.h"
#include "utils/MpiUtils.h"
#include "utils/MathUtils.h"
#include "executor/ot/one_of_two/RsaOtExecutor.h"

void RsaOtMultiplicationShareExecutor::obtainMultiplicationTriple() {
    generateRandomAB();

    computeU();
    computeV();
    computeC();

    if (_benchmarkLevel == BenchmarkLevel::DETAILED && _isLogBenchmark) {
        Log::i(BM_TAG + " OT RSA keys generation time: " + std::to_string(_otRsaGenerationTime) + " ms.");
        Log::i(BM_TAG + " OT RSA encryption time: " + std::to_string(_otRsaEncryptionTime) + " ms.");
        Log::i(BM_TAG + " OT RSA decryption time: " + std::to_string(_otRsaDecryptionTime) + " ms.");
        Log::i(BM_TAG + " OT MPI transmission and synchronization time: " + std::to_string(_otMpiTime) + " ms.");
        Log::i(BM_TAG + " OT total computation time: " + std::to_string(_otEntireComputationTime) + " ms.");
    }
}

void RsaOtMultiplicationShareExecutor::generateRandomAB() {
    _a0 = MathUtils::rand64(0, (1LL << _l) - 1);
    _b0 = MathUtils::rand64(0, (1LL << _l) - 1);
}

void RsaOtMultiplicationShareExecutor::computeU() {
    computeMix(0, _u0);
}

void RsaOtMultiplicationShareExecutor::computeV() {
    computeMix(1, _v0);
}

int64_t RsaOtMultiplicationShareExecutor::corr(int i, int64_t x) const {
    return MathUtils::ringMod((_a0 << i) - x, _l);
}

void RsaOtMultiplicationShareExecutor::computeMix(int sender, int64_t &mix) {
    bool isSender = MpiUtils::getMpiRank() == sender;
    int64_t sum = 0;
    for (int i = 0; i < _l; i++) {
        int64_t s0 = 0, s1 = 0;
        int choice = 0;
        if (isSender) {
            s0 = MathUtils::rand64(0, (1LL << _l) - 1);
            s1 = corr(i, s0);
        } else {
            choice = (int)((_b0 >> i) & 1);
        }
        RsaOtExecutor r(sender, s0, s1, choice);
        r.setLogBenchmark(false);
        if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
            r.setBenchmark(BenchmarkLevel::DETAILED);
        }
        r.compute();
        if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
            // add mpi time
            _mpiTime += r.getMpiTime();
            _otMpiTime += r.getMpiTime();
            _otRsaGenerationTime += r.getRsaGenerationTime();
            _otRsaEncryptionTime += r.getRsaEncryptionTime();
            _otRsaDecryptionTime += r.getRsaDecryptionTime();
            _otEntireComputationTime += r.getEntireComputationTime();
        }
        if (isSender) {
            sum += s0;
        } else {
            int64_t temp = r.getResult();
            if (choice == 0) {
                temp = MathUtils::ringMod(-r.getResult(), _l);
            }
            sum += temp;
        }
    }
    mix = MathUtils::ringMod(sum, _l);
}

void RsaOtMultiplicationShareExecutor::computeC() {
    _c0 = _a0 * _b0 + _u0 + _v0;
}