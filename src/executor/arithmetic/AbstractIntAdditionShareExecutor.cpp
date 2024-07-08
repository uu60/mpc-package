//
// Created by 杜建璋 on 2024/7/6.
//
#include "utils/Utils.h"
#include "executor/arithmetic/AbstractIntAdditionShareExecutor.h"

void AbstractIntAdditionShareExecutor::generateSaved() {
    // return random by default
    x1 = Utils::generateRandomInt();
    x2 = x - x1;
}

void AbstractIntAdditionShareExecutor::exchangePart() {
    Utils::exchangeData(&x2, &y2, mpiRank);
}

void AbstractIntAdditionShareExecutor::calculateTempResult() {
    temp = x1 + y2;
}

void AbstractIntAdditionShareExecutor::exchangeTempResult() {
    Utils::exchangeData(&temp, &recvTemp, mpiRank);
}

int AbstractIntAdditionShareExecutor::result() {
    calculate();
    finalize();
    return res;
}

void AbstractIntAdditionShareExecutor::initData() {
    // get holding param
    obtainX();
    // get saved
    generateSaved();
}

void AbstractIntAdditionShareExecutor::calculate() {
    generateSaved();
    exchangePart();
    calculateTempResult();
    exchangeTempResult();
    calculateResult();
}

void AbstractIntAdditionShareExecutor::calculateResult() {
    res = temp + recvTemp;
}

