//
// Created by 杜建璋 on 2024/8/30.
//

#ifndef MPC_PACKAGE_RSAOTANDSHAREEXECUTOR_H
#define MPC_PACKAGE_RSAOTANDSHAREEXECUTOR_H
#include "./AbstractAndShareExecutor.h"
#include "../../../bmt/RsaOtTripleGenerator.h"

class RsaOtAndShareExecutor : public AbstractAndShareExecutor {
public:
    RsaOtAndShareExecutor(bool x, bool y);
    RsaOtAndShareExecutor(bool x, bool y, bool dummy);
protected:
    void obtainMultiplicationTriple() override;
    [[nodiscard]] std::string tag() const override;
};


#endif //MPC_PACKAGE_RSAOTANDSHAREEXECUTOR_H
