//
// Created by 杜建璋 on 2024/7/6.
//

#ifndef UNTITLED1_TEST_H
#define UNTITLED1_TEST_H
#include "./mpc_package/executor/arithmetic/PartialAdditionExecutor.h"


class Test : public PartialAdditionExecutor {
protected:
    void obtainXA() override;

    void obtainYA() override;
};


#endif //UNTITLED1_TEST_H
