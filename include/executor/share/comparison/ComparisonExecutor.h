//
// Created by 杜建璋 on 2024/9/2.
//

#ifndef MPC_PACKAGE_COMPARISONEXECUTOR_H
#define MPC_PACKAGE_COMPARISONEXECUTOR_H
#include "../../AbstractExecutor.h"

class ComparisonExecutor : public AbstractExecutor {
private:
    // compare x and y
    // x = x0 + x1
    // y = y0 + y1
    int64_t x0{};
    int64_t y0{};

public:
    void compute() override;
};


#endif //MPC_PACKAGE_COMPARISONEXECUTOR_H
