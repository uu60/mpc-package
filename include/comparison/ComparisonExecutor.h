//
// Created by 杜建璋 on 2024/9/2.
//

#ifndef MPC_PACKAGE_COMPARISONEXECUTOR_H
#define MPC_PACKAGE_COMPARISONEXECUTOR_H

#include "../arithmetic/IntShareExecutor.h"

template<typename T>
class ComparisonExecutor : public IntShareExecutor<T> {
private:
    T _cvtZ{};
    bool _sign{};
public:
    ComparisonExecutor(T x, T y);

    ComparisonExecutor(T xi, T yi, bool dummy);

    ComparisonExecutor *execute(bool reconstruct) override;

    ComparisonExecutor *reconstruct() override;

    [[nodiscard]] std::string tag() const override;

private:
    ComparisonExecutor *convertZToBoolShare();
};


#endif //MPC_PACKAGE_COMPARISONEXECUTOR_H
