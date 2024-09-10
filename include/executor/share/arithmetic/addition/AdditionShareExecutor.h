//
// Created by 杜建璋 on 2024/7/13.
//

#ifndef MPC_PACKAGE_ADDITIONSHAREEXECUTOR_H
#define MPC_PACKAGE_ADDITIONSHAREEXECUTOR_H

#include "../../../../executor/share/AbstractIntegerShareExecutor.h"

class AdditionShareExecutor : public AbstractIntegerShareExecutor {
public:
    AdditionShareExecutor(int64_t x, int64_t y);
    AdditionShareExecutor(int64_t xi, int64_t yi, bool dummy); // dummy just for overload
    void compute() override;
protected:
    [[nodiscard]] std::string tag() const override;
};


#endif //MPC_PACKAGE_ADDITIONSHAREEXECUTOR_H
