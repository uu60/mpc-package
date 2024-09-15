//
// Created by 杜建璋 on 2024/7/13.
//

#ifndef MPC_PACKAGE_ADDITIONSHAREEXECUTOR_H
#define MPC_PACKAGE_ADDITIONSHAREEXECUTOR_H

#include "../../../../executor/share/IntShareExecutor.h"
#include <vector>

template<typename T>
class AdditionShareExecutor : public IntShareExecutor<T> {
private:
    enum class Mode {
        DUAL,
        ARRAY
    };

    Mode mode = Mode::DUAL;
public:
    AdditionShareExecutor(T x, T y);

    AdditionShareExecutor(T xi, T yi, bool dummy); // dummy just for overload
    explicit AdditionShareExecutor(std::vector<T>& xis);

    AdditionShareExecutor *execute(bool reconstruct) override;

protected:
    [[nodiscard]] std::string tag() const override;
};


#endif //MPC_PACKAGE_ADDITIONSHAREEXECUTOR_H
