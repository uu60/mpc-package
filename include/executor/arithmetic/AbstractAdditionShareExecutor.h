//
// Created by 杜建璋 on 2024/7/6.
//

#ifndef MPC_PACKAGE_ABSTRACTADDITIONSHAREEXECUTOR_H
#define MPC_PACKAGE_ABSTRACTADDITIONSHAREEXECUTOR_H


#include "executor/AbstractExecutor.h"

class AbstractAdditionShareExecutor : public AbstractExecutor {
protected:
    // holding param
    int x{};
    // saved part (a random int)
    int x1{};
    // left part = x - x1
    int x2{};
    // received number (part of the other's holding)
    int y2{};
    // temp result (part sum)
    int temp{};
    // received temp result (from the other)
    int recvTemp{};
    // final result
    int res{};
protected:
    // must define how to obtain holding param
    virtual void obtainX() = 0;

    // define how to generate saved part of x
    virtual void generateSaved();

    void initData() override;

public:
    // get calculated result
    int result() override;

private:
    // exchange part
    void exchangePart();

    // calculate temp result
    void calculateTempResult();

    // exchange temp result
    void exchangeTempResult();

    // calculate result
    void calculateResult();

    // calculate process
    void calculate();
};


#endif //MPC_PACKAGE_ABSTRACTADDITIONSHAREEXECUTOR_H
