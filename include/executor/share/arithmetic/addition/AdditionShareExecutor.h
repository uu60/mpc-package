//
// Created by 杜建璋 on 2024/7/13.
//

#ifndef MPC_PACKAGE_ADDITIONSHAREEXECUTOR_H
#define MPC_PACKAGE_ADDITIONSHAREEXECUTOR_H

#include "../../../Executor.h"

class AdditionShareExecutor : public Executor {
protected:
    /*
     * Alice holds _x = _x0 + _x1
     * Bob holds y = _y0 + y1
     * compute _x + y => _z0 + _z1 = (_x0 + _y0) + (y1 + _x1)
     */
    int64_t _x{};
    int64_t _x0{};
    int64_t _x1{};
    int64_t _y0{};
    int64_t _z0{};
    int64_t _z1{};
public:
    explicit AdditionShareExecutor(int64_t x);
    void compute() override;
protected:
    [[nodiscard]] std::string tag() const override;
};


#endif //MPC_PACKAGE_ADDITIONSHAREEXECUTOR_H
