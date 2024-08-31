//
// Created by 杜建璋 on 2024/8/29.
//

#ifndef MPC_PACKAGE_ABSTRACTANDSHAREEXECUTOR_H
#define MPC_PACKAGE_ABSTRACTANDSHAREEXECUTOR_H
#include "../../../Executor.h"

class AbstractAndShareExecutor : public Executor {
protected:
    // secret
    int64_t _x{};
    // share
    int64_t _x0{};
    int64_t _x1{};
    // triple
    int64_t _a0{};
    int64_t _b0{};
    int64_t _c0{};

public:
    explicit AbstractAndShareExecutor(bool x);
    void compute() override;
protected:
    virtual void obtainMultiplicationTriple() = 0;
    [[nodiscard]] std::string tag() const override;
};


#endif //MPC_PACKAGE_ABSTRACTANDSHAREEXECUTOR_H
