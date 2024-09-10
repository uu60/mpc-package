//
// Created by 杜建璋 on 2024/9/6.
//

#ifndef MPC_PACKAGE_ABSTRACTBOOLSHAREEXECUTOR_H
#define MPC_PACKAGE_ABSTRACTBOOLSHAREEXECUTOR_H
#include "../../executor/AbstractExecutor.h"

class AbstractBoolShareExecutor : public AbstractExecutor {
protected:
    bool _xi{};
    bool _yi{};
public:
    AbstractBoolShareExecutor(int64_t x, int64_t y);
    AbstractBoolShareExecutor(int64_t xi, int64_t yi, bool dummy);
};


#endif //MPC_PACKAGE_ABSTRACTBOOLSHAREEXECUTOR_H
