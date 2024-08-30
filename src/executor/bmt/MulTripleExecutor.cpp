//
// Created by 杜建璋 on 2024/8/30.
//

#include "executor/bmt/MulTripleExecutor.h"
#include "executor/ot/RsaOtExecutor.h"
#include "utils/MathUtils.h"
#include "utils/MpiUtils.h"

MulTripleExecutor::MulTripleExecutor(int l) {
    _l = l;
}

void MulTripleExecutor::generateRandomAB() {
    _a0 = MathUtils::rand64(0, (1LL << _l) - 1);
    _b0 = MathUtils::rand64(0, (1LL << _l) - 1);
}

void MulTripleExecutor::computeU() {
    computeMix(0, _u0);
}

void MulTripleExecutor::computeV() {
    computeMix(1, _v0);
}

int64_t MulTripleExecutor::corr(int i, int64_t x) const {
    return MathUtils::ringMod((_a0 << i) - x, _l);
}

void MulTripleExecutor::computeMix(int sender, int64_t &mix) {
    bool isSender = MpiUtils::rank() == sender;
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
        r.logBenchmark(false);
        if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
            r.benchmark(BenchmarkLevel::DETAILED);
        }
        r.compute();
        if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
            // add mpi time
            _mpiTime += r.mpiTime();
            _otMpiTime += r.mpiTime();
            _otRsaGenerationTime += r.getRsaGenerationTime();
            _otRsaEncryptionTime += r.getRsaEncryptionTime();
            _otRsaDecryptionTime += r.getRsaDecryptionTime();
            _otEntireComputationTime += r.entireComputationTime();
        }
        if (isSender) {
            sum += s0;
        } else {
            int64_t temp = r.result();
            if (choice == 0) {
                temp = MathUtils::ringMod(-r.result(), _l);
            }
            sum += temp;
        }
    }
    mix = MathUtils::ringMod(sum, _l);
}

void MulTripleExecutor::computeC() {
    _c0 = MathUtils::ringMod(_a0 * _b0 + _u0 + _v0, _l);
}

int64_t MulTripleExecutor::a0() const {
    return _a0;
}

int64_t MulTripleExecutor::b0() const {
    return _b0;
}

int64_t MulTripleExecutor::c0() const {
    return _c0;
}

void MulTripleExecutor::compute() {
    generateRandomAB();

    computeU();
    computeV();
    computeC();
}

int64_t MulTripleExecutor::otRsaGenerationTime() const {
    return _otRsaGenerationTime;
}

int64_t MulTripleExecutor::otRsaEncryptionTime() const {
    return _otRsaEncryptionTime;
}

int64_t MulTripleExecutor::otRsaDecryptionTime() const {
    return _otRsaDecryptionTime;
}

int64_t MulTripleExecutor::otMpiTime() const {
    return _otMpiTime;
}

int64_t MulTripleExecutor::otEntireComputationTime() const {
    return _otEntireComputationTime;
}


std::string MulTripleExecutor::tag() const {
    return "[BMT Generator]";
}
