//
// Created by 杜建璋 on 2024/8/29.
//

#ifndef MPC_PACKAGE_ABSTRACTANDSHAREEXECUTOR_H
#define MPC_PACKAGE_ABSTRACTANDSHAREEXECUTOR_H
#include "../../../AbstractExecutor.h"

class AbstractAndShareExecutor : public AbstractExecutor {
protected:
    // secret
    bool _x{};
    // share
    bool _x0{};
    bool _x1{};
    // triple
    bool _a0{};
    bool _b0{};
    bool _c0{};

public:
    explicit AbstractAndShareExecutor(bool x);
    void compute() override;
protected:
    virtual void obtainMultiplicationTriple() = 0;
    [[nodiscard]] std::string tag() const override;
private:
    void process();
};


#endif //MPC_PACKAGE_ABSTRACTANDSHAREEXECUTOR_H
