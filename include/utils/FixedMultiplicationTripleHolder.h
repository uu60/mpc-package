//
// Created by 杜建璋 on 2024/7/27.
//

#ifndef MPC_PACKAGE_FIXEDMULTIPLICATIONTRIPLEHOLDER_H
#define MPC_PACKAGE_FIXEDMULTIPLICATIONTRIPLEHOLDER_H

#include <iostream>
#include <tuple>
#include <array>

class FixedMultiplicationTripleHolder {
private:
    static const std::array<std::tuple<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>, std::pair<uint64_t,
            uint64_t>>, 100> TRIPLES_4;

    static const std::array<std::tuple<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>>, 100> TRIPLES_8;

    static const std::array<std::tuple<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>>, 100> TRIPLES_16;

    static const std::array<std::tuple<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>>, 100> TRIPLES_32;

    static const std::array<std::tuple<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>>, 100> TRIPLES_64;

public:
    static std::tuple<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>> getRandomTriple(int idx, int bits);

};


#endif //MPC_PACKAGE_FIXEDMULTIPLICATIONTRIPLEHOLDER_H
