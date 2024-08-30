//
// Created by 杜建璋 on 2024/7/27.
//

#ifndef DEMO_FIXEDMULTIPLICATIONSHAREEXECUTOR_H
#define DEMO_FIXEDMULTIPLICATIONSHAREEXECUTOR_H
#include "MulShareExecutor.h"
#include <array>
#include <utility>  // For std::pair
#include <tuple>   // For std::tuple

class FixedMulShareExecutor : public MulShareExecutor {
public:
    FixedMulShareExecutor(int64_t x, int l) : MulShareExecutor(x, l) {}

protected:
    [[nodiscard]] std::string tag() const override;
    void obtainMultiplicationTriple() override;
private:
    std::tuple<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>> getRandomTriple(int idx);

// fixed MTs
private:
    static const std::array<std::tuple<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>, std::pair<uint64_t,
            uint64_t>>, 100> TRIPLES_4;

    static const std::array<std::tuple<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>>, 100> TRIPLES_8;

    static const std::array<std::tuple<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>>, 100> TRIPLES_16;

    static const std::array<std::tuple<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>>, 100> TRIPLES_32;

    static const std::array<std::tuple<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>>, 100> TRIPLES_64;
};


#endif //DEMO_FIXEDMULTIPLICATIONSHAREEXECUTOR_H
