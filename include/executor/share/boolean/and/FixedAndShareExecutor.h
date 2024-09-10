//
// Created by 杜建璋 on 2024/8/30.
//

#ifndef MPC_PACKAGE_FIXEDANDSHAREEXECUTOR_H
#define MPC_PACKAGE_FIXEDANDSHAREEXECUTOR_H
#include "../../boolean/and/AbstractAndShareExecutor.h"

class FixedAndShareExecutor : public AbstractAndShareExecutor {
public:
    FixedAndShareExecutor(bool x, bool y);
    FixedAndShareExecutor(bool x, bool y, bool dummy);

protected:
    void obtainMultiplicationTriple() override;
    [[nodiscard]] std::string tag() const override;
};


#endif //MPC_PACKAGE_FIXEDANDSHAREEXECUTOR_H
