//
// Created by 杜建璋 on 2024/7/6.
//

#ifndef UNTITLED1_TEST_H
#define UNTITLED1_TEST_H
#include "./mpc_package/executor/arithmetic/AdditiveExecutor.h"


class Test : public AdditiveExecutor {
protected:
    void obtainX1() override;

    void obtainY1() override;
};


#endif //UNTITLED1_TEST_H
