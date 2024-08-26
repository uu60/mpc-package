//
// Created by 杜建璋 on 2024/7/12.
//

#ifndef MPC_PACKAGE_PARTIALADDITIONSHAREEXECUTOR_H
#define MPC_PACKAGE_PARTIALADDITIONSHAREEXECUTOR_H

#include "executor/Executor.h"

class PartialAdditionShareExecutor : public Executor {
protected:
    /*
     * Alice holds _x0 and _y0
     * Bob holds _x1 and y1
     * compute _x + y => _z0 + _z1 = (_x0 + _y0) + (_x1 + y1)
     */

    // part of _x
    int64_t _x0{};
    // part of y
    int64_t _y0{};
    int64_t _z0{};
    int64_t _z1{};

public:
    PartialAdditionShareExecutor(int64_t x0, int64_t y0);
    // compute process
    void compute() override;
};


#endif //MPC_PACKAGE_PARTIALADDITIONSHAREEXECUTOR_H
