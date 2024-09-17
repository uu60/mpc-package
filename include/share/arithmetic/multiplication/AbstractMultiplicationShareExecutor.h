//
// Created by 杜建璋 on 2024/7/13.
//

#ifndef MPC_PACKAGE_ABSTRACTMULTIPLICATIONSHAREEXECUTOR_H
#define MPC_PACKAGE_ABSTRACTMULTIPLICATIONSHAREEXECUTOR_H
#include "../../../share/arithmetic/IntShareExecutor.h"

template<typename T>
class AbstractMultiplicationShareExecutor : public IntShareExecutor<T> {
protected:
    T _ai{};
    T _bi{};
    T _ci{};

public:
    AbstractMultiplicationShareExecutor(T x, T y);
    AbstractMultiplicationShareExecutor(T xi, T yi, bool dummy);
    AbstractMultiplicationShareExecutor* execute(bool reconstruct) override;

protected:
    virtual void obtainMultiplicationTriple() = 0;

private:
    void process(bool reconstruct);
};


#endif //MPC_PACKAGE_ABSTRACTMULTIPLICATIONSHAREEXECUTOR_H
