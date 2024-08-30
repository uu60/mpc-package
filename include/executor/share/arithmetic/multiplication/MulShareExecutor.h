//
// Created by 杜建璋 on 2024/7/13.
//

#ifndef MPC_PACKAGE_MULSHAREEXECUTOR_H
#define MPC_PACKAGE_MULSHAREEXECUTOR_H
#include "../../../Executor.h"

class MulShareExecutor : public Executor {
protected:
    // hold
    int64_t _x{};
    // parts
    // _x = _x0 + _x1
    // y = _y0 + yb
    int64_t _x0{};
    int64_t _x1{};
    // MT
    // _a0, _b0, _c0 belongs to Alice
    // c = (_c0 + c1) = a * b = (_a0 + a1) * (_b0 + b1)
    int _l{};
    int64_t _a0{};
    int64_t _b0{};
    int64_t _c0{};

public:
    MulShareExecutor(int64_t x, int l);
    void compute() override;

protected:
    virtual void obtainMultiplicationTriple() = 0;

private:
    void process();
};


#endif //MPC_PACKAGE_MULSHAREEXECUTOR_H
