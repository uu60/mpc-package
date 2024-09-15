//
// Created by 杜建璋 on 2024/7/27.
//

#ifndef MPC_PACKAGE_RSAOTMULTIPLICATIONSHAREEXECUTOR_H
#define MPC_PACKAGE_RSAOTMULTIPLICATIONSHAREEXECUTOR_H
#include "../../arithmetic/multiplication/AbstractMultiplicationShareExecutor.h"

template<typename T>
class RsaOtMultiplicationShareExecutor : public AbstractMultiplicationShareExecutor<T> {
public:
    RsaOtMultiplicationShareExecutor(T x, T y);
    RsaOtMultiplicationShareExecutor(T x, T y, bool dummy);
protected:
    void obtainMultiplicationTriple() override;
    [[nodiscard]] std::string tag() const override;
};


#endif //MPC_PACKAGE_RSAOTMULTIPLICATIONSHAREEXECUTOR_H
