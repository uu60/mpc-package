//
// Created by 杜建璋 on 2024/7/13.
//

#ifndef MPC_PACKAGE_ABSTRACTMULTIPLICATIONSHAREEXECUTOR_H
#define MPC_PACKAGE_ABSTRACTMULTIPLICATIONSHAREEXECUTOR_H
#include "../../../../executor/share/AbstractIntegerShareExecutor.h"

class AbstractMultiplicationShareExecutor : public AbstractIntegerShareExecutor {
protected:
    // MT
    // _ai, _bi, _ci belongs to Alice
    // c = (_ci + c1) = a * b = (_ai + a1) * (_bi + b1)
    int _l{};
    int64_t _ai{};
    int64_t _bi{};
    int64_t _ci{};

public:
    AbstractMultiplicationShareExecutor(int64_t x, int64_t y, int l);
    AbstractMultiplicationShareExecutor(int64_t xi, int64_t yi, int l, bool dummy);
    void compute() override;

protected:
    virtual void obtainMultiplicationTriple() = 0;

private:
    void process();
};


#endif //MPC_PACKAGE_ABSTRACTMULTIPLICATIONSHAREEXECUTOR_H
