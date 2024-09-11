//
// Created by 杜建璋 on 2024/7/13.
//

#ifndef MPC_PACKAGE_ADDITIONSHAREEXECUTOR_H
#define MPC_PACKAGE_ADDITIONSHAREEXECUTOR_H

#include "../../../../executor/share/AbstractIntShareExecutor.h"
#include <vector>

class AdditionShareExecutor : public AbstractIntShareExecutor {
private:
    enum class Mode {
        DUAL,
        ARRAY
    };

    Mode mode = Mode::DUAL;
public:
    AdditionShareExecutor(int64_t x, int64_t y, int l);

    AdditionShareExecutor(int64_t xi, int64_t yi, int l, bool dummy); // dummy just for overload
    AdditionShareExecutor(std::vector<int64_t>& xis, int l);

    AdditionShareExecutor *execute() override;

protected:
    [[nodiscard]] std::string tag() const override;
};


#endif //MPC_PACKAGE_ADDITIONSHAREEXECUTOR_H
