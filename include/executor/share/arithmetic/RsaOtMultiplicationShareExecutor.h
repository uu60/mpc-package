//
// Created by 杜建璋 on 2024/7/27.
//

#ifndef MPC_PACKAGE_RSAOTMULTIPLICATIONSHAREEXECUTOR_H
#define MPC_PACKAGE_RSAOTMULTIPLICATIONSHAREEXECUTOR_H
#include "../../../executor/share/arithmetic/MultiplicationShareExecutor.h"


class RsaOtMultiplicationShareExecutor : public MultiplicationShareExecutor {
public:
    RsaOtMultiplicationShareExecutor(int64_t x, int l) : MultiplicationShareExecutor(x, l) {}
protected:
    void obtainMultiplicationTriple() override;
};


#endif //MPC_PACKAGE_RSAOTMULTIPLICATIONSHAREEXECUTOR_H
