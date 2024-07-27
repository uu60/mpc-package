//
// Created by 杜建璋 on 2024/7/13.
//

#include "executor/share/arithmetic/MultiplicationShareExecutor.h"
#include "utils/MpiUtils.h"
#include "utils/MathUtils.h"
#include "executor/ot/one_of_two/RsaOtExecutor.h"
#include "utils/Log.h"

const std::string MultiplicationShareExecutor::BM_TAG = "[Multiplication Share]";

MultiplicationShareExecutor::MultiplicationShareExecutor(int64_t x, int l) {
    // data
    _x = x;
    _x1 = MathUtils::rand64();
    _x0 = _x - _x1;

    _l = l >= 64 ? 64 : (l >= 32 ? 32 : (l >= 16 ? 16 : (l >= 8 ? 8 : 4)));
}

void MultiplicationShareExecutor::compute() {
    int64_t start, end, end1;
    if (_benchmark) {
        start = System::currentTimeMillis();
    }
    // MT
    obtainMultiplicationTriple();
    if (_benchmark) {
        end = System::currentTimeMillis();
        Log::i(BM_TAG + " Triple computation time: " + std::to_string(end - start) + " ms.");
    }
    // process
    process();
    if (_benchmark) {
        end1 = System::currentTimeMillis();
        Log::i(BM_TAG + " MPI transmission and synchronization time: " + std::to_string(_mpiTime) + " ms.");
        Log::i(BM_TAG + " Entire computation time: " + std::to_string(end1 - start) + " ms.");
    }
}

void MultiplicationShareExecutor::process() {
    int64_t x0, y0, *self, *other;
    self = MpiUtils::getMpiRank() == 0 ? &x0 : &y0;
    other = MpiUtils::getMpiRank() == 0 ? &y0 : &x0;
    *self = _x0;
    if (_benchmark) {
        MpiUtils::exchange(&_x1, other, _mpiTime);
    } else {
        MpiUtils::exchange(&_x1, other);
    }
    int64_t e0 = x0 - _a0;
    int64_t f0 = y0 - _b0;
    int64_t e1, f1;
    if (_benchmark) {
        MpiUtils::exchange(&e0, &e1, _mpiTime);
        MpiUtils::exchange(&f0, &f1, _mpiTime);
    } else {
        MpiUtils::exchange(&e0, &e1);
        MpiUtils::exchange(&f0, &f1);
    }
    int64_t e = e0 + e1;
    int64_t f = f0 + f1;
    int64_t z0 = MpiUtils::getMpiRank() * e * f + f * _a0 + e * _b0 + _c0;
    int64_t z1;
    if (_benchmark) {
        MpiUtils::exchange(&z0, &z1, _mpiTime);
    } else {
        MpiUtils::exchange(&z0, &z1);
    }
    _res = MathUtils::ringMod(z0 + z1, _l);
}

void MultiplicationShareExecutor::generateRandomAB() {
    _a0 = MathUtils::rand64(0, (1LL << _l) - 1);
    _b0 = MathUtils::rand64(0, (1LL << _l) - 1);
}

void MultiplicationShareExecutor::computeU() {
    computeMix(0, _u0);
}

void MultiplicationShareExecutor::computeV() {
    computeMix(1, _v0);
}

int64_t MultiplicationShareExecutor::corr(int i, int64_t x) const {
    return MathUtils::ringMod((_a0 << i) - x, _l);
}

void MultiplicationShareExecutor::computeMix(int sender, int64_t &mix) {
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
        if (_benchmark) {
            r.setBenchmark(true);
        }
        r.compute();
        if (_benchmark) {
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

void MultiplicationShareExecutor::computeC() {
    _c0 = _a0 * _b0 + _u0 + _v0;
}
