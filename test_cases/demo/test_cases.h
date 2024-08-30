//
// Created by 杜建璋 on 2024/8/29.
//

#ifndef DEMO_TEST_CASES_H
#define DEMO_TEST_CASES_H
#include "mpc_package/utils/Log.h"
#include "mpc_package/utils/MpiUtils.h"
#include "mpc_package/utils/MathUtils.h"
#include "mpc_package/executor/share/boolean/xor/XorBoolShareExecutor.h"
#include "mpc_package/executor/share/boolean/and/AndBoolShareExecutor.h"
#include "mpc_package/executor/share/arithmetic/multiplication/FixedMulShareExecutor.h"
#include "mpc_package/executor/share/arithmetic/multiplication//RsaOtMulShareExecutor.h"

void test_FixedMultiplicationShareExecutor() {
    int a = MathUtils::rand32();
    Log::i("Multiplier: " + std::to_string(a));
    FixedMulShareExecutor m(a, 32);
    m.benchmark(BenchmarkLevel::DETAILED);
    m.logBenchmark(true);
    m.compute();
    Log::i(std::to_string((m.result())));
}

void test_RsaOtMultiplicationShareExecutor() {
    int a = MathUtils::rand32();
    Log::i("Multiplier: " + std::to_string(a));
    RsaOtMulShareExecutor m(a, 32);
    m.benchmark(BenchmarkLevel::DETAILED);
    m.logBenchmark(true);
    m.compute();
    Log::i(std::to_string((m.result())));
}

void test_XorBooleanShareExecutor() {
    bool a = MathUtils::rand32(0, 1);
    Log::i("Boolean: " + std::to_string(a));
    XorBoolShareExecutor e(a);
    e.benchmark(BenchmarkLevel::DETAILED);
    e.logBenchmark(true);
    e.compute();
    Log::d(std::to_string(e.result()));
}

void test_AndBoolShareExecutor() {
    bool a = MathUtils::rand32(0, 1);
    Log::i("Boolean: " + std::to_string(a));
    AndBoolShareExecutor e(a);
    e.benchmark(BenchmarkLevel::DETAILED);
    e.compute();
    Log::d(std::to_string(e.result()));
}

#endif //DEMO_TEST_CASES_H
