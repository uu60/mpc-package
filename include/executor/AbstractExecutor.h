//
// Created by 杜建璋 on 2024/7/7.
//

#ifndef MPC_PACKAGE_ABSTRACTEXECUTOR_H
#define MPC_PACKAGE_ABSTRACTEXECUTOR_H

#include <cstdint>
#include <string>
#include "../utils/System.h"
#include "../utils/Log.h"

class AbstractExecutor {
public:
    enum class BenchmarkLevel {
        NONE, GENERAL, DETAILED
    };
protected:
    // result
    int64_t _result{};

    // for benchmark
    BenchmarkLevel _benchmarkLevel = BenchmarkLevel::NONE;
    bool _isLogBenchmark = false;
    int64_t _mpiTime{};
    int64_t _entireComputationTime{};
public:
    // secret sharing process
    virtual AbstractExecutor* execute() = 0;
    // get calculated result
    [[nodiscard]] int64_t result() const;
    AbstractExecutor* benchmark(BenchmarkLevel lv);
    AbstractExecutor* logBenchmark(bool isLogBenchmark);
    [[nodiscard]] int64_t mpiTime() const;
    [[nodiscard]] int64_t entireComputationTime() const;
protected:
    [[nodiscard]] virtual std::string tag() const = 0;
    virtual void finalize();
};

#endif //MPC_PACKAGE_ABSTRACTEXECUTOR_H
