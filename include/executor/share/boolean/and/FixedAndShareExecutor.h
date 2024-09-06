//
// Created by 杜建璋 on 2024/8/30.
//

#ifndef MPC_PACKAGE_FIXEDANDSHAREEXECUTOR_H
#define MPC_PACKAGE_FIXEDANDSHAREEXECUTOR_H
#include "AbstractAndShareExecutor.h"

class FixedAndShareExecutor : public AbstractAndShareExecutor {
public:
    explicit FixedAndShareExecutor(bool x, bool y) : AbstractAndShareExecutor(x, y) {};

protected:
    void obtainMultiplicationTriple() override;
    [[nodiscard]] std::string tag() const override;
};


#endif //MPC_PACKAGE_FIXEDANDSHAREEXECUTOR_H
