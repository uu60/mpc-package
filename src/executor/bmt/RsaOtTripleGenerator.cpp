//
// Created by 杜建璋 on 2024/8/30.
//

#include "executor/bmt/RsaOtTripleGenerator.h"
#include "executor/ot/RsaOtExecutor.h"
#include "utils/Math.h"
#include "utils/Mpi.h"

RsaOtTripleGenerator::RsaOtTripleGenerator(int l) {
    _l = l;
}

void RsaOtTripleGenerator::generateRandomAB() {
    _ai = Math::rand64(0, (1LL << _l) - 1);
    _bi = Math::rand64(0, (1LL << _l) - 1);
}

void RsaOtTripleGenerator::computeU() {
    computeMix(0, _ui);
}

void RsaOtTripleGenerator::computeV() {
    computeMix(1, _vi);
}

int64_t RsaOtTripleGenerator::corr(int i, int64_t x) const {
    return Math::ringMod((_ai << i) - x, _l);
}

void RsaOtTripleGenerator::computeMix(int sender, int64_t &mix) {
    bool isSender = Mpi::rank() == sender;
    int64_t sum = 0;
    for (int i = 0; i < _l; i++) {
        int64_t s0 = 0, s1 = 0;
        int choice = 0;
        if (isSender) {
            s0 = Math::rand64(0, (1LL << _l) - 1);
            s1 = corr(i, s0);
        } else {
            choice = (int) ((_bi >> i) & 1);
        }
        RsaOtExecutor r(sender, s0, s1, choice);
        r.logBenchmark(false);
        if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
            r.benchmark(BenchmarkLevel::DETAILED);
        }
        r.execute();
        if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
            // add mpi time
            _mpiTime += r.mpiTime();
            _otMpiTime += r.mpiTime();
            _otRsaGenerationTime += r.rsaGenerationTime();
            _otRsaEncryptionTime += r.rsaEncryptionTime();
            _otRsaDecryptionTime += r.rsaDecryptionTime();
            _otEntireComputationTime += r.entireComputationTime();
        }
        if (isSender) {
            sum += s0;
        } else {
            int64_t temp = r.result();
            if (choice == 0) {
                temp = Math::ringMod(-r.result(), _l);
            }
            sum += temp;
        }
    }
    mix = Math::ringMod(sum, _l);
}

void RsaOtTripleGenerator::computeC() {
    _ci = Math::ringMod(_ai * _bi + _ui + _vi, _l);
}

RsaOtTripleGenerator* RsaOtTripleGenerator::execute() {
    generateRandomAB();

    computeU();
    computeV();
    computeC();
    return this;
}

int64_t RsaOtTripleGenerator::otRsaGenerationTime() const {
    return _otRsaGenerationTime;
}

int64_t RsaOtTripleGenerator::otRsaEncryptionTime() const {
    return _otRsaEncryptionTime;
}

int64_t RsaOtTripleGenerator::otRsaDecryptionTime() const {
    return _otRsaDecryptionTime;
}

int64_t RsaOtTripleGenerator::otMpiTime() const {
    return _otMpiTime;
}

int64_t RsaOtTripleGenerator::otEntireComputationTime() const {
    return _otEntireComputationTime;
}


std::string RsaOtTripleGenerator::tag() const {
    return "[BMT Generator]";
}
