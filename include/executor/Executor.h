//
// Created by 杜建璋 on 2024/7/7.
//

#ifndef MPC_PACKAGE_EXECUTOR_H
#define MPC_PACKAGE_EXECUTOR_H

#include <cstdint>
#include "../utils/System.h"
#include "../utils/Log.h"

class Executor {
protected:
    // getResult
    int64_t _res{};
    bool _benchmark = false;
    int64_t _mpiTime{};
public:
    // secret sharing process
    virtual void compute() = 0;
    // get calculated getResult
    [[nodiscard]] int64_t getResult() const;
    void setBenchmark(bool enabled);
    [[nodiscard]] int64_t getMpiTime() const;
protected:
    virtual void finalize();
};

#endif //MPC_PACKAGE_EXECUTOR_H
