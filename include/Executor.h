//
// Created by 杜建璋 on 2024/7/7.
//

#ifndef MPC_PACKAGE_EXECUTOR_H
#define MPC_PACKAGE_EXECUTOR_H

#include <cstdint>
#include <string>
#include "./utils/System.h"
#include "./utils/Log.h"

using namespace std;

template<typename T>
class Executor {
public:
    enum class BenchmarkLevel {
        NONE, GENERAL, DETAILED
    };
protected:
    // result
    T _result{};

    // _l
    const int _l = std::is_same_v<T, bool> ? 1 : sizeof _result * 8;

    // for benchmark
    BenchmarkLevel _benchmarkLevel = BenchmarkLevel::NONE;
    bool _isLogBenchmark = false;
    int64_t _mpiTime{};
    int64_t _entireComputationTime{};
public:
    // secret sharing process
    virtual Executor* execute(bool reconstruct);
    virtual Executor* reconstruct();
    // get calculated result
    [[nodiscard]] T result() const;
    Executor* benchmark(BenchmarkLevel lv);
    Executor* logBenchmark(bool isLogBenchmark);
    [[nodiscard]] int64_t mpiTime() const;
    [[nodiscard]] int64_t entireComputationTime() const;
protected:
    [[nodiscard]] virtual std::string tag() const;
    virtual void finalize();
};

#endif //MPC_PACKAGE_EXECUTOR_H
