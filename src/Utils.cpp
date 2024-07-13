//
// Created by 杜建璋 on 2024/7/6.
//

#include "utils/Utils.h"
#include "random"

int Utils::randomInt() {
    // random engine
    std::random_device rd;
    std::mt19937 generator(rd());

    // distribution in integer range
    std::uniform_int_distribution<int> distribution(-RAND_MAX - 1, RAND_MAX);

    // generation
    return distribution(generator);
}
