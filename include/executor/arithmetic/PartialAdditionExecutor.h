//
// Created by 杜建璋 on 2024/7/12.
//

#ifndef MPC_PACKAGE_PARTIALADDITIONEXECUTOR_H
#define MPC_PACKAGE_PARTIALADDITIONEXECUTOR_H

#include "../Executor.h"

class PartialAdditionExecutor : public Executor {
protected:
    /*
     * Alice holds xa and ya
     * Bob holds xb and yb
     * compute x + y => za + zb = (xa + ya) + (xb + yb)
     */

    // part of x
    int xa{};
    // part of y
    int ya{};
    int za{};
    int zb{};

public:
    void init() override;

    // compute process
    void compute() override;

protected:
    virtual void obtainXA() = 0;

    virtual void obtainYA() = 0;
};


#endif //MPC_PACKAGE_PARTIALADDITIONEXECUTOR_H
