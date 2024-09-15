//
// Created by 杜建璋 on 2024/9/2.
//

#ifndef MPC_PACKAGE_COMPARISONEXECUTOR_H
#define MPC_PACKAGE_COMPARISONEXECUTOR_H
#include "../IntShareExecutor.h"

template<typename T>
class ComparisonExecutor : public IntShareExecutor<T> {
public:
    // if (x > y) 1
    // if (x = y) 0
    // if (x < y) -1
    ComparisonExecutor(T x, T y);
    ComparisonExecutor(T xi, T yi, bool dummy);
    ComparisonExecutor* execute(bool reconstruct) override;
};


#endif //MPC_PACKAGE_COMPARISONEXECUTOR_H
