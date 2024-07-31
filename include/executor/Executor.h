//
// Created by 杜建璋 on 2024/7/7.
//

#ifndef MPC_PACKAGE_EXECUTOR_H
#define MPC_PACKAGE_EXECUTOR_H

#include <cstdint>
#include "../utils/System.h"
#include "../utils/Log.h"

enum class BenchmarkLevel {
    NONE, GENERAL, DETAILED
};

class Executor {
protected:
    // getResult
    int64_t _res{};

    // for benchmark
    BenchmarkLevel _benchmarkLevel = BenchmarkLevel::NONE;
    bool _isLogBenchmark = false;
    int64_t _mpiTime{};
    int64_t _entireComputationTime{};
public:
    // secret sharing process
    virtual void compute() = 0;
    // get calculated getResult
    [[nodiscard]] int64_t getResult() const;
    void setBenchmark(BenchmarkLevel lv);
    void setLogBenchmark(bool isLogBenchmark);
    [[nodiscard]] int64_t getMpiTime() const;
    [[nodiscard]] int64_t getEntireComputationTime() const;
protected:
    virtual void finalize();
};

#endif //MPC_PACKAGE_EXECUTOR_H
