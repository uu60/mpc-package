//
// Created by 杜建璋 on 2024/7/13.
//

#ifndef MPC_PACKAGE_MULTIPLICATIONSHAREEXECUTOR_H
#define MPC_PACKAGE_MULTIPLICATIONSHAREEXECUTOR_H
#include "share/ShareExecutor.h"

class MultiplicationShareExecutor : public ShareExecutor {
protected:
    // hold
    int64_t _x{};
    // parts
    // _x = _xa + _xb
    // y = _ya + yb
    int64_t _xa{};
    int64_t _xb{};
    // MT
    // _aa, _ba, _ca belongs to Alice
    // c = (_ca + cb) = a * b = (_aa + ab) * (_ba + bb)
    int _l{};
    int64_t _aa{};
    int64_t _ba{};
    int64_t _ca{};
    int64_t _ua{};
    int64_t _va{};

public:
    MultiplicationShareExecutor(int64_t x, int l);
    void compute() override;

private:
    void obtainMultiplicationTriple();
};


#endif //MPC_PACKAGE_MULTIPLICATIONSHAREEXECUTOR_H
