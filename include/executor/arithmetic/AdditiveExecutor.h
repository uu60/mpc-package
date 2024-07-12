//
// Created by 杜建璋 on 2024/7/12.
//

#ifndef MPC_PACKAGE_ADDITIVEEXECUTOR_H
#define MPC_PACKAGE_ADDITIVEEXECUTOR_H

#include "../Executor.h"

class AdditiveExecutor : public Executor {
protected:
    int x1{};
    int y1{};
    int z1{};
    int z2{};

public:
    void init() override;

    // compute process
    void compute() override;

protected:
    virtual void obtainX1() = 0;

    virtual void obtainY1() = 0;
};


#endif //MPC_PACKAGE_ADDITIVEEXECUTOR_H
