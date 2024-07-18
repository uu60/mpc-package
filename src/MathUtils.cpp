//
// Created by 杜建璋 on 2024/7/6.
//

#include "utils/MathUtils.h"
#include "random"

int MathUtils::randomInt() {
    return randomInt(-RAND_MAX - 1, RAND_MAX);
}

int MathUtils::randomInt(int lowest, int highest) {
    // random engine
    std::random_device rd;
    std::mt19937 generator(rd());

    // distribution in integer range
    std::uniform_int_distribution<int> distribution(lowest, highest);

    // generation
    return distribution(generator);
}

int MathUtils::pow(int base, int exponent) {
    int result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result *= base;
        }
        base *= base;
        exponent /= 2;
    }
    return result;
}
