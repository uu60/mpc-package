//
// Created by 杜建璋 on 2024/8/30.
//

#ifndef MPC_PACKAGE_FIXEDTRIPLEEXECUTOR_H
#define MPC_PACKAGE_FIXEDTRIPLEEXECUTOR_H
#include "AbstractMulTripleExecutor.h"

class FixedTripleExecutor : public AbstractMulTripleExecutor {
private:
    std::tuple<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>> getRandomTriple(int idx);
public:
    explicit FixedTripleExecutor(int l);
    void compute() override;
protected:
    [[nodiscard]] std::string tag() const override;
// fixed MTs
private:
    static const std::array<std::tuple<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>, std::pair<uint64_t,
            uint64_t>>, 100> TRIPLES_1;

    static const std::array<std::tuple<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>, std::pair<uint64_t,
            uint64_t>>, 100> TRIPLES_4;

    static const std::array<std::tuple<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>>, 100> TRIPLES_8;

    static const std::array<std::tuple<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>>, 100> TRIPLES_16;

    static const std::array<std::tuple<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>>, 100> TRIPLES_32;

    static const std::array<std::tuple<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>>, 100> TRIPLES_64;
};


#endif //MPC_PACKAGE_FIXEDTRIPLEEXECUTOR_H
