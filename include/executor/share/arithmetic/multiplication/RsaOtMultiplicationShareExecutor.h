//
// Created by 杜建璋 on 2024/7/27.
//

#ifndef MPC_PACKAGE_RSAOTMULTIPLICATIONSHAREEXECUTOR_H
#define MPC_PACKAGE_RSAOTMULTIPLICATIONSHAREEXECUTOR_H
#include "AbstractMultiplicationShareExecutor.h"


class RsaOtMultiplicationShareExecutor : public AbstractMultiplicationShareExecutor {
public:
    RsaOtMultiplicationShareExecutor(int64_t x, int l) : AbstractMultiplicationShareExecutor(x, l) {}
protected:
    void obtainMultiplicationTriple() override;
    [[nodiscard]] std::string tag() const override;
};


#endif //MPC_PACKAGE_RSAOTMULTIPLICATIONSHAREEXECUTOR_H
