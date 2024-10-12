//
// Created by 杜建璋 on 2024/8/29.
//

#ifndef MPC_PACKAGE_ABSTRACTANDSHAREEXECUTOR_H
#define MPC_PACKAGE_ABSTRACTANDSHAREEXECUTOR_H
#include "../../boolean/BoolShareExecutor.h"

class AbstractAndShareExecutor : public BoolShareExecutor {
protected:
    // triple
    bool _ai{};
    bool _bi{};
    bool _ci{};

public:
    AbstractAndShareExecutor(bool x, bool y);
    AbstractAndShareExecutor(bool xi, bool yi, bool dummy);
    AbstractAndShareExecutor* execute(bool reconstruct) override;
protected:
    virtual void obtainMultiplicationTriple() = 0;
    [[nodiscard]] std::string tag() const override;
private:
    void process(bool reconstruct);
};


#endif //MPC_PACKAGE_ABSTRACTANDSHAREEXECUTOR_H
