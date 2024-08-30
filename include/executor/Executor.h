//
// Created by 杜建璋 on 2024/7/7.
//

#ifndef MPC_PACKAGE_EXECUTOR_H
#define MPC_PACKAGE_EXECUTOR_H

#include <cstdint>
#include <string>
#include "../utils/System.h"
#include "../utils/Log.h"

enum class BenchmarkLevel {
    NONE, GENERAL, DETAILED
};

class Executor {
protected:
    // result
    int64_t _res{};

    // for benchmark
    BenchmarkLevel _benchmarkLevel = BenchmarkLevel::NONE;
    bool _isLogBenchmark = false;
    int64_t _mpiTime{};
    int64_t _entireComputationTime{};
public:
    // secret sharing process
    virtual void compute() = 0;
    // get calculated result
    [[nodiscard]] int64_t result() const;
    void benchmark(BenchmarkLevel lv);
    void logBenchmark(bool isLogBenchmark);
    [[nodiscard]] int64_t mpiTime() const;
    [[nodiscard]] int64_t entireComputationTime() const;
protected:
    [[nodiscard]] virtual std::string tag() const = 0;
    virtual void finalize();
};

#endif //MPC_PACKAGE_EXECUTOR_H
