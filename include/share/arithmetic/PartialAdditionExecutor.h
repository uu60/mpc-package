//
// Created by 杜建璋 on 2024/7/12.
//

#ifndef MPC_PACKAGE_PARTIALADDITIONEXECUTOR_H
#define MPC_PACKAGE_PARTIALADDITIONEXECUTOR_H

#include "share/Executor.h"

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
    void init(int xa, int ya);

    // compute process
    void compute() override;
};


#endif //MPC_PACKAGE_PARTIALADDITIONEXECUTOR_H
