//
// Created by 杜建璋 on 2024/8/29.
//

#ifndef MPC_PACKAGE_ABSTRACTANDSHAREEXECUTOR_H
#define MPC_PACKAGE_ABSTRACTANDSHAREEXECUTOR_H
#include "../../../AbstractExecutor.h"

class AbstractAndShareExecutor : public AbstractExecutor {
protected:
    // secret share
    bool _xi{};
    bool _yi{};
    // triple
    bool _ai{};
    bool _bi{};
    bool _ci{};

public:
    explicit AbstractAndShareExecutor(bool x, bool y);
    void compute() override;
protected:
    virtual void obtainMultiplicationTriple() = 0;
    [[nodiscard]] std::string tag() const override;
private:
    void process();
};


#endif //MPC_PACKAGE_ABSTRACTANDSHAREEXECUTOR_H
