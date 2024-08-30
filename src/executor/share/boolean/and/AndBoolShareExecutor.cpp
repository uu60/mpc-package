//
// Created by 杜建璋 on 2024/8/29.
//

#include "executor/share/boolean/and/AndBoolShareExecutor.h"
#include "utils/MathUtils.h"
#include "utils/MpiUtils.h"
#include "executor/bmt/MulTripleExecutor.h"

AndBoolShareExecutor::AndBoolShareExecutor(bool x) {
    _x = x;
    _x1 = MathUtils::rand32(0, 1);
    _x0 = _x1 xor _x;

    // triple
    _a0 = MathUtils::rand32(0, 1);
    _b0 = MathUtils::rand32(0, 1);
    _c0 = _a0 and _b0;
}

void AndBoolShareExecutor::compute() {
    // BMT
    obtainMultiplicationTriple();

    // process
    /*
     * For member variables, x represents part of own secret,
     * which means that for party[0], x represents x in paper,
     * for party[1], that is y in paper.
     *
     * For all the variables in this project, subscript of a
     * variable represents the party who will use that to
     * compute. For example, x0 is used by executor itself
     * while x1 is used by the other one.
     * */
    int64_t x0, y0, *self, *other;
    self = MpiUtils::rank() == 0 ? &x0 : &y0;
    other = MpiUtils::rank() == 0 ? &y0 : &x0;
    *self = _x0;
    MpiUtils::exchange(&_x1, other);
    int64_t e0 = _a0 xor x0;
    int64_t f0 = _b0 xor y0;
    int64_t e1, f1;
    MpiUtils::exchange(&e0, &e1);
    MpiUtils::exchange(&f0, &f1);
    int64_t e = e0 xor e1;
    int64_t f = f0 xor f1;
    int64_t z0 = MpiUtils::rank() * e * f xor f * _a0 xor e * _b0 xor _c0;
    int64_t z1;
    MpiUtils::exchange(&z0, &z1);
    _res = z0 xor z1;
}

void AndBoolShareExecutor::obtainMultiplicationTriple() {
    MulTripleExecutor m(1);
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

std::string AndBoolShareExecutor::tag() const {
    return "[And Boolean Share]";
}
