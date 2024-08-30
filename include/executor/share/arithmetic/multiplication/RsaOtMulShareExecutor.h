//
// Created by 杜建璋 on 2024/7/27.
//

#ifndef MPC_PACKAGE_RSAOTMULSHAREEXECUTOR_H
#define MPC_PACKAGE_RSAOTMULSHAREEXECUTOR_H
#include "AbstractMulShareExecutor.h"


class RsaOtMulShareExecutor : public AbstractMulShareExecutor {
public:
    RsaOtMulShareExecutor(int64_t x, int l) : AbstractMulShareExecutor(x, l) {}
protected:
    void obtainMultiplicationTriple() override;
    [[nodiscard]] std::string tag() const override;
};


#endif //MPC_PACKAGE_RSAOTMULSHAREEXECUTOR_H
