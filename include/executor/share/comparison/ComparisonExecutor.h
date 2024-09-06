//
// Created by 杜建璋 on 2024/9/2.
//

#ifndef MPC_PACKAGE_COMPARISONEXECUTOR_H
#define MPC_PACKAGE_COMPARISONEXECUTOR_H
#include "../AbstractIntegerShareExecutor.h"

class ComparisonExecutor : public AbstractIntegerShareExecutor {
public:
    // if (x > y) 1
    // if (x = y) 0
    // if (x < y) -1
    ComparisonExecutor(int64_t x, int64_t y);
    ComparisonExecutor(int64_t xi, int64_t yi, bool dummy);
    void compute() override;
};


#endif //MPC_PACKAGE_COMPARISONEXECUTOR_H
