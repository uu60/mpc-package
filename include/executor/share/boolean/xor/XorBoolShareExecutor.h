//
// Created by 杜建璋 on 2024/8/29.
//

#ifndef MPC_PACKAGE_XORBOOLSHAREEXECUTOR_H
#define MPC_PACKAGE_XORBOOLSHAREEXECUTOR_H

#include "../../../Executor.h"
class XorBoolShareExecutor : public Executor {
private:
    // secret
    int64_t _x{};
    // for share
    int64_t _x0{};
    int64_t _x1{};
    int64_t _y0{};
    // temp result
    int64_t _z0{};
    int64_t _z1{};
public:
    explicit XorBoolShareExecutor(bool x);
    void compute() override;
protected:
    [[nodiscard]] std::string tag() const override;
};


#endif //MPC_PACKAGE_XORBOOLSHAREEXECUTOR_H
