//
// Created by 杜建璋 on 2024/7/27.
//

#ifndef DEMO_FIXEDMULTIPLICATIONSHAREEXECUTOR_H
#define DEMO_FIXEDMULTIPLICATIONSHAREEXECUTOR_H
#include "mpc_package/executor/share/arithmetic/MultiplicationShareExecutor.h"

class FixedMultiplicationShareExecutor : public MultiplicationShareExecutor {
public:
    FixedMultiplicationShareExecutor(int64_t x, int l) : MultiplicationShareExecutor(x, l) {}
protected:
    void obtainMultiplicationTriple() override;
};


#endif //DEMO_FIXEDMULTIPLICATIONSHAREEXECUTOR_H
