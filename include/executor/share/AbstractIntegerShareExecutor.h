//
// Created by 杜建璋 on 2024/9/6.
//

#ifndef MPC_PACKAGE_ABSTRACTINTEGERSHAREEXECUTOR_H
#define MPC_PACKAGE_ABSTRACTINTEGERSHAREEXECUTOR_H
#include "../../executor/AbstractExecutor.h"


class AbstractIntegerShareExecutor : public AbstractExecutor {
protected:
    int64_t _xi{};
    int64_t _yi{};
public:
    AbstractIntegerShareExecutor(int64_t x, int64_t y);
    AbstractIntegerShareExecutor(int64_t xi, int64_t yi, bool dummy);
};


#endif //MPC_PACKAGE_ABSTRACTINTEGERSHAREEXECUTOR_H
