//
// Created by 杜建璋 on 2024/7/7.
//

#include <iostream>
#include "share/Executor.h"
#include "utils/MpiUtils.h"
#include "mpi.h"

void Executor::finalize() {
    // do nothing by default
}

int Executor::result() const {
    return res;
}

void Executor::inited() {
    // do nothing by default
}
