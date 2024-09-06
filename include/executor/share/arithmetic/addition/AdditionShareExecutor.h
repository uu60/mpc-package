//
// Created by 杜建璋 on 2024/7/13.
//

#ifndef MPC_PACKAGE_ADDITIONSHAREEXECUTOR_H
#define MPC_PACKAGE_ADDITIONSHAREEXECUTOR_H

#include "../../../AbstractExecutor.h"

class AdditionShareExecutor : public AbstractExecutor {
protected:
    /*
     * Alice holds _x = _xi + _x1
     * Bob holds y = _yi + y1
     * compute _x + y => _z0 + _z1 = (_xi + _yi) + (y1 + _x1)
     */
    int64_t _xi{};
    int64_t _yi{};

public:
    explicit AdditionShareExecutor(int64_t x, int64_t y);
    void compute() override;
protected:
    [[nodiscard]] std::string tag() const override;
};


#endif //MPC_PACKAGE_ADDITIONSHAREEXECUTOR_H
