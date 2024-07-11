//
// Created by 杜建璋 on 2024/7/6.
//

#ifndef UNTITLED1_TEST_H
#define UNTITLED1_TEST_H
#include "./executor/arithmetic/AbstractDemoAdditionShareExecutor.h"


class Test : public AbstractDemoAdditionShareExecutor {
private:
    void obtainX() override;
};


#endif //UNTITLED1_TEST_H
