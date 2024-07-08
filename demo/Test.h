//
// Created by 杜建璋 on 2024/7/6.
//

#ifndef UNTITLED1_TEST_H
#define UNTITLED1_TEST_H
#include "./executor/arithmetic/AbstractIntAdditionShareExecutor.h"


class Test : public AbstractIntAdditionShareExecutor {
private:
    void obtainX() override;
};


#endif //UNTITLED1_TEST_H
