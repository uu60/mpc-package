//
// Created by 杜建璋 on 2024/8/29.
//

#ifndef MPC_PACKAGE_ANDBOOLSHAREEXECUTOR_H
#define MPC_PACKAGE_ANDBOOLSHAREEXECUTOR_H
#include "../../../Executor.h"

class AndBoolShareExecutor : public Executor {
private:
    // secret
    int64_t _x{};
    // share
    int64_t _x0{};
    int64_t _x1{};
    int64_t _y0{};
    // triple
    int64_t _a0{};
    int64_t _b0{};
    int64_t _c0{};

public:
    explicit AndBoolShareExecutor(bool x);
    void compute() override;
protected:
    void obtainMultiplicationTriple();
    [[nodiscard]] std::string tag() const override;
};


#endif //MPC_PACKAGE_ANDBOOLSHAREEXECUTOR_H
