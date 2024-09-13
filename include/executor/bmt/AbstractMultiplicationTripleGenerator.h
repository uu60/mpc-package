//
// Created by 杜建璋 on 2024/8/30.
//

#ifndef MPC_PACKAGE_ABSTRACTMULTIPLICATIONTRIPLEGENERATOR_H
#define MPC_PACKAGE_ABSTRACTMULTIPLICATIONTRIPLEGENERATOR_H

#include "../Executor.h"

class AbstractMultiplicationTripleGenerator : public Executor {
protected:
    int _l{};
    int64_t _ai{};
    int64_t _bi{};
    int64_t _ci{};
    int64_t _ui{};
    int64_t _vi{};
protected:
    AbstractMultiplicationTripleGenerator *reconstruct() override;

public:
    [[nodiscard]] int64_t ai() const;

    [[nodiscard]] int64_t bi() const;

    [[nodiscard]] int64_t ci() const;
};


#endif //MPC_PACKAGE_ABSTRACTMULTIPLICATIONTRIPLEGENERATOR_H
