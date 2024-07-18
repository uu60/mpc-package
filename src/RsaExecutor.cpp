//
// Created by 杜建璋 on 2024/7/15.
//

#include "ot/one_of_two/RsaExecutor.h"
#include "utils/MpiUtils.h"

RsaExecutor::RsaExecutor(int bits0) {
    bits = bits0;
}


void RsaExecutor::compute() {
    // as a sender
    if (sender == MpiUtils::getMpiRank()) {

    }

}