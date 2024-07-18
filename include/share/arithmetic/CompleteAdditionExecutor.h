//
// Created by 杜建璋 on 2024/7/13.
//

#ifndef MPC_PACKAGE_COMPLETEADDITIONEXECUTOR_H
#define MPC_PACKAGE_COMPLETEADDITIONEXECUTOR_H
#include "share/Executor.h"

class CompleteAdditionExecutor : public Executor {
protected:
    /*
     * Alice holds x = xa + xb
     * Bob holds y = ya + yb
     * compute x + y => za + zb = (xa + ya) + (yb + xb)
     */
    int x{};
    int xa{};
    int xb{};
    int ya{};
    int za{};
    int zb{};
public:
    void compute() override;
    void init(int x);
};


#endif //MPC_PACKAGE_COMPLETEADDITIONEXECUTOR_H
