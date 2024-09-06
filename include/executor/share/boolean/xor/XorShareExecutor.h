//
// Created by 杜建璋 on 2024/8/29.
//

#ifndef MPC_PACKAGE_XORSHAREEXECUTOR_H
#define MPC_PACKAGE_XORSHAREEXECUTOR_H

#include "../AbstractBoolShareExecutor.h"
class XorShareExecutor : public AbstractBoolShareExecutor {
public:
   XorShareExecutor(bool x, bool y);
    void compute() override;
protected:
    [[nodiscard]] std::string tag() const override;
};


#endif //MPC_PACKAGE_XORSHAREEXECUTOR_H
