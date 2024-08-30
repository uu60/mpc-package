//
// Created by 杜建璋 on 2024/8/30.
//

#ifndef MPC_PACKAGE_MULTRIPLEEXECUTOR_H
#define MPC_PACKAGE_MULTRIPLEEXECUTOR_H
#include "../Executor.h"
#include <iostream>

class MulTripleExecutor : public Executor {
private:
    // benchmark
    BenchmarkLevel _benchmarkLevel = BenchmarkLevel::NONE;
    int64_t _otRsaGenerationTime{};
    int64_t _otRsaEncryptionTime{};
    int64_t _otRsaDecryptionTime{};
    int64_t _otMpiTime{};
    int64_t _otEntireComputationTime{};
    int _l{};
    int64_t _a0{};
    int64_t _b0{};
    int64_t _c0{};
    int64_t _u0{};
    int64_t _v0{};
public:
    explicit MulTripleExecutor(int l);
    void compute() override;
private:
    void generateRandomAB();
    void computeU();
    void computeV();
    void computeMix(int sender, int64_t &mix);
    void computeC();
    [[nodiscard]] int64_t corr(int i, int64_t x) const;
public:
    [[nodiscard]] int64_t a0() const;
    [[nodiscard]] int64_t b0() const;
    [[nodiscard]] int64_t c0() const;
    [[nodiscard]] int64_t otRsaGenerationTime() const;
    [[nodiscard]] int64_t otRsaEncryptionTime() const;
    [[nodiscard]] int64_t otRsaDecryptionTime() const;
    [[nodiscard]] int64_t otMpiTime() const;
    [[nodiscard]] int64_t otEntireComputationTime() const;
protected:
    [[nodiscard]] std::string tag() const override;
};


#endif //MPC_PACKAGE_MULTRIPLEEXECUTOR_H
