//
// Created by 杜建璋 on 2024/9/6.
//

#ifndef MPC_PACKAGE_INTSHAREEXECUTOR_H
#define MPC_PACKAGE_INTSHAREEXECUTOR_H

#include "../../executor/AbstractExecutor.h"


class IntShareExecutor : public AbstractExecutor {
protected:
    int _l{};
    int64_t _xi{};
    int64_t _yi{};
    int64_t _zi{};
public:
    [[nodiscard]] int64_t xi() const;
    IntShareExecutor *zi(int64_t zi);

public:
    IntShareExecutor();

    IntShareExecutor(int64_t x, int l);

    IntShareExecutor(int64_t x, int64_t y, int l);

    IntShareExecutor(int64_t xi, int64_t yi, int l, bool dummy);

    // Do not use the following methods!
    IntShareExecutor *execute(bool reconstruct) override;

    IntShareExecutor *reconstruct() override;

    [[nodiscard]] std::string

    tag() const override;
};


#endif //MPC_PACKAGE_INTSHAREEXECUTOR_H
