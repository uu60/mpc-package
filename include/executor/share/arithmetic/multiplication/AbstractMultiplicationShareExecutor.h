//
// Created by 杜建璋 on 2024/7/13.
//

#ifndef MPC_PACKAGE_ABSTRACTMULTIPLICATIONSHAREEXECUTOR_H
#define MPC_PACKAGE_ABSTRACTMULTIPLICATIONSHAREEXECUTOR_H
#include "../../../../executor/share/IntShareExecutor.h"

class AbstractMultiplicationShareExecutor : public IntShareExecutor {
protected:
    int _l{};
    int64_t _ai{};
    int64_t _bi{};
    int64_t _ci{};

public:
    AbstractMultiplicationShareExecutor(int64_t x, int64_t y, int l);
    AbstractMultiplicationShareExecutor(int64_t xi, int64_t yi, int l, bool dummy);
    AbstractMultiplicationShareExecutor* execute(bool reconstruct) override;

protected:
    virtual void obtainMultiplicationTriple() = 0;

public:
    AbstractMultiplicationShareExecutor *reconstruct() override;

private:
    void process(bool reconstruct);
};


#endif //MPC_PACKAGE_ABSTRACTMULTIPLICATIONSHAREEXECUTOR_H
