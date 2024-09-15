//
// Created by 杜建璋 on 2024/7/27.
//

#ifndef DEMO_FIXEDMULTIPLICATIONSHAREEXECUTOR_H
#define DEMO_FIXEDMULTIPLICATIONSHAREEXECUTOR_H
#include "../../arithmetic/multiplication/AbstractMultiplicationShareExecutor.h"

template<typename T>
class FixedMultiplicationShareExecutor : public AbstractMultiplicationShareExecutor<T> {
public:
    FixedMultiplicationShareExecutor(T x, T y);
    FixedMultiplicationShareExecutor(T x, T y, bool dummy);

protected:
    [[nodiscard]] std::string tag() const override;
    void obtainMultiplicationTriple() override;
};


#endif //DEMO_FIXEDMULTIPLICATIONSHAREEXECUTOR_H
