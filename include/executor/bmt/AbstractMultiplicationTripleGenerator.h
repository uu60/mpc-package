//
// Created by 杜建璋 on 2024/8/30.
//

#ifndef MPC_PACKAGE_ABSTRACTMULTIPLICATIONTRIPLEGENERATOR_H
#define MPC_PACKAGE_ABSTRACTMULTIPLICATIONTRIPLEGENERATOR_H
#include "../AbstractExecutor.h"

class AbstractMultiplicationTripleGenerator : public AbstractExecutor {
protected:
    int _l{};
    int64_t _ai{};
    int64_t _bi{};
    int64_t _ci{};
    int64_t _ui{};
    int64_t _vi{};
public:
    [[nodiscard]] int64_t getAi() const;
    [[nodiscard]] int64_t getBi() const;
    [[nodiscard]] int64_t getCi() const;
};


#endif //MPC_PACKAGE_ABSTRACTMULTIPLICATIONTRIPLEGENERATOR_H
