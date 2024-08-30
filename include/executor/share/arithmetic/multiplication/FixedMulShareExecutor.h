//
// Created by 杜建璋 on 2024/7/27.
//

#ifndef DEMO_FIXEDMULTIPLICATIONSHAREEXECUTOR_H
#define DEMO_FIXEDMULTIPLICATIONSHAREEXECUTOR_H
#include "AbstractMulShareExecutor.h"
#include <array>
#include <utility>  // For std::pair
#include <tuple>   // For std::tuple

class FixedMulShareExecutor : public AbstractMulShareExecutor {
public:
    FixedMulShareExecutor(int64_t x, int l) : AbstractMulShareExecutor(x, l) {}

protected:
    [[nodiscard]] std::string tag() const override;
    void obtainMultiplicationTriple() override;
};


#endif //DEMO_FIXEDMULTIPLICATIONSHAREEXECUTOR_H
