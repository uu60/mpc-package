//
// Created by 杜建璋 on 2024/9/2.
//

#ifndef MPC_PACKAGE_COMPARISONEXECUTOR_H
#define MPC_PACKAGE_COMPARISONEXECUTOR_H
#include "../AbstractIntShareExecutor.h"

class ComparisonExecutor : public AbstractIntShareExecutor {
public:
    // if (x > y) 1
    // if (x = y) 0
    // if (x < y) -1
    ComparisonExecutor(int64_t x, int64_t y, int l);
    ComparisonExecutor(int64_t xi, int64_t yi, int l, bool dummy);
    ComparisonExecutor* execute() override;
};


#endif //MPC_PACKAGE_COMPARISONEXECUTOR_H
