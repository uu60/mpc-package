//
// Created by 杜建璋 on 2024/9/6.
//

#ifndef MPC_PACKAGE_BOOLSHAREEXECUTOR_H
#define MPC_PACKAGE_BOOLSHAREEXECUTOR_H
#include "../../executor/Executor.h"

class BoolShareExecutor : public Executor {
protected:
    bool _xi{};
    bool _yi{};
    bool _zi{};
public:
    BoolShareExecutor(int64_t x, int64_t y);
    BoolShareExecutor(int64_t xi, int64_t yi, bool dummy);

    Executor * reconstruct() override;

    Executor *execute(bool reconstruct) override;

protected:
    std::string tag() const override;
};


#endif //MPC_PACKAGE_BOOLSHAREEXECUTOR_H
