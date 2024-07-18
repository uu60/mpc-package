//
// Created by 杜建璋 on 2024/7/13.
//

#ifndef MPC_PACKAGE_MULTIPLICATIONEXECUTOR_H
#define MPC_PACKAGE_MULTIPLICATIONEXECUTOR_H
#include "share/Executor.h"

class MultiplicationExecutor : public Executor {
protected:
    // hold
    int x{};
    // parts
    // x = xa + xb
    // y = ya + yb
    int xa{};
    int xb{};
    // MT
    // aa, ba, ca belongs to Alice
    // c = (ca + cb) = a * b = (aa + ab) * (ba + bb)
    int l{};
    int aa{};
    int ba{};
    int ca{};
    int ua{};
    int va{};

public:
    void init(int x, int l);
    void compute() override;

private:
    void obtainMultiplicationTriple();
};


#endif //MPC_PACKAGE_MULTIPLICATIONEXECUTOR_H
