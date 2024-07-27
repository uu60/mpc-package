//
// Created by 杜建璋 on 2024/7/27.
//

#ifndef MPC_PACKAGE_RSAOTMULTIPLICATIONSHAREEXECUTOR_H
#define MPC_PACKAGE_RSAOTMULTIPLICATIONSHAREEXECUTOR_H
#include "../../../executor/share/arithmetic/MultiplicationShareExecutor.h"


class RsaOtMultiplicationShareExecutor : public MultiplicationShareExecutor {
public:
    RsaOtMultiplicationShareExecutor(int64_t x, int l) : MultiplicationShareExecutor(x, l) {}
protected:
    void obtainMultiplicationTriple() override;
private:
    void generateRandomAB();
    void computeU();
    void computeV();
    void computeMix(int sender, int64_t &mix);
    void computeC();
    [[nodiscard]] int64_t corr(int i, int64_t x) const;
};


#endif //MPC_PACKAGE_RSAOTMULTIPLICATIONSHAREEXECUTOR_H
