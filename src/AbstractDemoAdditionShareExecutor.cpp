//
// Created by 杜建璋 on 2024/7/6.
//
#include "utils/Utils.h"
#include "demo/AbstractDemoAdditionShareExecutor.h"

void AbstractDemoAdditionShareExecutor::generateSaved() {
    // return random by default
    x1 = Utils::generateRandomInt();
    x2 = x - x1;
}

void AbstractDemoAdditionShareExecutor::exchangePart() {
    Utils::exchangeData(&x2, &y2, mpiRank);
}

void AbstractDemoAdditionShareExecutor::calculateTempResult() {
    temp = x1 + y2;
}

void AbstractDemoAdditionShareExecutor::exchangeTempResult() {
    Utils::exchangeData(&temp, &recvTemp, mpiRank);
}

void AbstractDemoAdditionShareExecutor::generateShare() {
    // get holding param
    obtainX();
    // get saved
    generateSaved();
}

void AbstractDemoAdditionShareExecutor::compute() {
    generateSaved();
    exchangePart();
    calculateTempResult();
    exchangeTempResult();
    calculateResult();
}

void AbstractDemoAdditionShareExecutor::calculateResult() {
    res = {temp + recvTemp};
}

