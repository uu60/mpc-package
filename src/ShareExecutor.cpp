//
// Created by 杜建璋 on 2024/7/7.
//

#include <iostream>
#include "share/ShareExecutor.h"
#include "utils/MpiUtils.h"
#include <mpi.h>

void ShareExecutor::finalize() {
    // do nothing by default
}

int64_t ShareExecutor::result() const {
    return _res;
}

