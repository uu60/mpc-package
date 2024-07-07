//
// Created by 杜建璋 on 2024/7/6.
//
#include "utils/Utils.h"
#include "executor/arithmetic/AbstractAdditionShareExecutor.h"

void AbstractAdditionShareExecutor::generateSaved() {
    // return random by default
    x1 = Utils::generateRandomInt();
    x2 = x - x1;
}

void AbstractAdditionShareExecutor::exchangePart() {
    Utils::exchangeData(&x2, &y2, mpiRank);
}

void AbstractAdditionShareExecutor::calculateTempResult() {
    temp = x1 + y2;
}

void AbstractAdditionShareExecutor::exchangeTempResult() {
    Utils::exchangeData(&temp, &recvTemp, mpiRank);
}

int AbstractAdditionShareExecutor::result() {
    calculate();
    finalize();
    return res;
}

void AbstractAdditionShareExecutor::initData() {
    // get holding param
    obtainX();
    // get saved
    generateSaved();
}

void AbstractAdditionShareExecutor::calculate() {
    generateSaved();
    exchangePart();
    calculateTempResult();
    exchangeTempResult();
    calculateResult();
}

void AbstractAdditionShareExecutor::calculateResult() {
    res = temp + recvTemp;
}

