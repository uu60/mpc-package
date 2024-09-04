//
// Created by 杜建璋 on 2024/9/2.
//

#ifndef MPC_PACKAGE_COMPARISONEXECUTOR_H
#define MPC_PACKAGE_COMPARISONEXECUTOR_H
#include "../../AbstractExecutor.h"

class ComparisonExecutor : public AbstractExecutor {
private:
    int64_t x{};
public:
    void compute() override;
};


#endif //MPC_PACKAGE_COMPARISONEXECUTOR_H
