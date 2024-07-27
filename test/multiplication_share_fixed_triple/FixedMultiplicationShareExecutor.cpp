//
// Created by 杜建璋 on 2024/7/27.
//

#include "FixedMultiplicationShareExecutor.h"
#include "mpc_package/utils/MpiUtils.h"
#include "mpc_package/utils/MathUtils.h"
#include "mpc_package/utils/FixedMultiplicationTripleHolder.h"
#include "mpc_package/utils/Log.h"
#include <iostream>

void FixedMultiplicationShareExecutor::obtainMultiplicationTriple() {
    int64_t idx = 0;
    if (MpiUtils::getMpiRank() == 0) {
        idx = MathUtils::rand64(0, 99);
        MpiUtils::send(&idx);
    } else {
        MpiUtils::recv(&idx);
    }
    std::tuple<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>> triple = FixedMultiplicationTripleHolder::getRandomTriple(
            (int) idx, 32);
    if (MpiUtils::getMpiRank() == 0) {
        _a0 = (int64_t) std::get<0>(triple).first;
        _b0 = (int64_t) std::get<1>(triple).first;
        _c0 = (int64_t) std::get<2>(triple).first;
    } else {
        _a0 = (int64_t) std::get<0>(triple).second;
        _b0 = (int64_t) std::get<1>(triple).second;
        _c0 = (int64_t) std::get<2>(triple).second;
    }
}
