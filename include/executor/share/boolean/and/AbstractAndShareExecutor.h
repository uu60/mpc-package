//
// Created by 杜建璋 on 2024/8/29.
//

#ifndef MPC_PACKAGE_ABSTRACTANDSHAREEXECUTOR_H
#define MPC_PACKAGE_ABSTRACTANDSHAREEXECUTOR_H
#include "../../../../executor/share/AbstractBoolShareExecutor.h"

class AbstractAndShareExecutor : public AbstractBoolShareExecutor {
protected:
    // triple
    bool _ai{};
    bool _bi{};
    bool _ci{};

public:
    AbstractAndShareExecutor(bool x, bool y);
    AbstractAndShareExecutor(bool x, bool y, bool dummy);
    AbstractAndShareExecutor* execute() override;
protected:
    virtual void obtainMultiplicationTriple() = 0;
    [[nodiscard]] std::string tag() const override;
private:
    void process();
};


#endif //MPC_PACKAGE_ABSTRACTANDSHAREEXECUTOR_H
