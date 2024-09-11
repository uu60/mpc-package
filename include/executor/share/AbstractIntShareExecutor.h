//
// Created by 杜建璋 on 2024/9/6.
//

#ifndef MPC_PACKAGE_ABSTRACTINTSHAREEXECUTOR_H
#define MPC_PACKAGE_ABSTRACTINTSHAREEXECUTOR_H
#include "../../executor/AbstractExecutor.h"


class AbstractIntShareExecutor : public AbstractExecutor {
protected:
    int _l{};
    int64_t _xi{};
    int64_t _yi{};
public:
    AbstractIntShareExecutor();
    AbstractIntShareExecutor(int64_t x, int64_t y, int l);
    AbstractIntShareExecutor(int64_t xi, int64_t yi, int l, bool dummy);
};


#endif //MPC_PACKAGE_ABSTRACTINTSHAREEXECUTOR_H
