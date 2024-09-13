//
// Created by 杜建璋 on 2024/8/30.
//

#ifndef MPC_PACKAGE_RSAOTTRIPLEGENERATOR_H
#define MPC_PACKAGE_RSAOTTRIPLEGENERATOR_H
#include "../Executor.h"
#include "AbstractMultiplicationTripleGenerator.h"
#include <iostream>

class RsaOtTripleGenerator : public AbstractMultiplicationTripleGenerator {
private:
    // benchmark
    int64_t _otRsaGenerationTime{};
    int64_t _otRsaEncryptionTime{};
    int64_t _otRsaDecryptionTime{};
    int64_t _otMpiTime{};
    int64_t _otEntireComputationTime{};
public:
    explicit RsaOtTripleGenerator(int l);
    RsaOtTripleGenerator* execute(bool dummy) override;
private:
    void generateRandomAB();
    void computeU();
    void computeV();
    void computeMix(int sender, int64_t &mix);
    void computeC();
    [[nodiscard]] int64_t corr(int i, int64_t x) const;
public:
    [[nodiscard]] int64_t otRsaGenerationTime() const;
    [[nodiscard]] int64_t otRsaEncryptionTime() const;
    [[nodiscard]] int64_t otRsaDecryptionTime() const;
    [[nodiscard]] int64_t otMpiTime() const;
    [[nodiscard]] int64_t otEntireComputationTime() const;
protected:
    [[nodiscard]] std::string tag() const override;
};


#endif //MPC_PACKAGE_RSAOTTRIPLEGENERATOR_H
