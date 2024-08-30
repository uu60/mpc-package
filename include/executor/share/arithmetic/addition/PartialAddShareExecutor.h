//
// Created by 杜建璋 on 2024/7/12.
//

#ifndef MPC_PACKAGE_PARTIALADDSHAREEXECUTOR_H
#define MPC_PACKAGE_PARTIALADDSHAREEXECUTOR_H

#include "../../../Executor.h"

class PartialAddShareExecutor : public Executor {
protected:
    /*
     * Alice holds _x0 and _y0
     * Bob holds _x1 and y1
     * compute _x + y => _z0 + _z1 = (_x0 + _y0) + (_x1 + y1)
     */

    // part of _x
    int64_t _x0{};
    // part of y
    int64_t _y0{};
    int64_t _z0{};
    int64_t _z1{};

public:
    PartialAddShareExecutor(int64_t x0, int64_t y0);
    // compute process
    void compute() override;
protected:
    [[nodiscard]] std::string tag() const override;
};


#endif //MPC_PACKAGE_PARTIALADDSHAREEXECUTOR_H
