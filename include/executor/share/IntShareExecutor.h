//
// Created by 杜建璋 on 2024/9/6.
//

#ifndef MPC_PACKAGE_INTSHAREEXECUTOR_H
#define MPC_PACKAGE_INTSHAREEXECUTOR_H

#include "../../executor/Executor.h"

template<typename T>
class IntShareExecutor : public Executor<T> {
protected:
    T _xi{};
    T _yi{};
    T _zi{};
public:
    [[nodiscard]] T xi() const;

    IntShareExecutor *zi(T zi);

public:
    IntShareExecutor();

    explicit IntShareExecutor(T x);

    IntShareExecutor(T x, T y);

    IntShareExecutor(T xi, T yi, bool dummy);

    IntShareExecutor *reconstruct() override;

    // Do not use the following methods!
    IntShareExecutor *execute(bool reconstruct) override;

    [[nodiscard]] std::string tag() const override;
};


#endif //MPC_PACKAGE_INTSHAREEXECUTOR_H
