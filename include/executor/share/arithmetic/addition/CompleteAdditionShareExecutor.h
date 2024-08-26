//
// Created by 杜建璋 on 2024/7/13.
//

#ifndef MPC_PACKAGE_COMPLETEADDITIONSHAREEXECUTOR_H
#define MPC_PACKAGE_COMPLETEADDITIONSHAREEXECUTOR_H

#include "executor/Executor.h"

class CompleteAdditionShareExecutor : public Executor {
protected:
    /*
     * Alice holds _x = _x0 + _x1
     * Bob holds y = _y0 + y1
     * compute _x + y => _z0 + _z1 = (_x0 + _y0) + (y1 + _x1)
     */
    int64_t _x{};
    int64_t _x0{};
    int64_t _x1{};
    int64_t _y0{};
    int64_t _z0{};
    int64_t _z1{};
public:
    explicit CompleteAdditionShareExecutor(int64_t x);
    void compute() override;
};


#endif //MPC_PACKAGE_COMPLETEADDITIONSHAREEXECUTOR_H
