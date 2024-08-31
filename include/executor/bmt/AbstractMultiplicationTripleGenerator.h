//
// Created by 杜建璋 on 2024/8/30.
//

#ifndef MPC_PACKAGE_ABSTRACTMULTIPLICATIONTRIPLEGENERATOR_H
#define MPC_PACKAGE_ABSTRACTMULTIPLICATIONTRIPLEGENERATOR_H
#include "../Executor.h"

class AbstractMultiplicationTripleGenerator : public Executor {
protected:
    int _l{};
    int64_t _a0{};
    int64_t _b0{};
    int64_t _c0{};
    int64_t _u0{};
    int64_t _v0{};
public:
    [[nodiscard]] int64_t a0() const;
    [[nodiscard]] int64_t b0() const;
    [[nodiscard]] int64_t c0() const;
};


#endif //MPC_PACKAGE_ABSTRACTMULTIPLICATIONTRIPLEGENERATOR_H
