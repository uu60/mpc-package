//
// Created by 杜建璋 on 2024/7/7.
//

#include <iostream>
#include "executor/Executor.h"
#include "utils/MpiUtils.h"
#include <mpi.h>

void Executor::finalize() {
    // do nothing by default
}

int64_t Executor::getResult() const {
    return _res;
}

void Executor::setBenchmark(bool enabled) {
    _benchmark = enabled;
}

int64_t Executor::getMpiTime() const {
    return _mpiTime;
}

