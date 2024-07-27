//
// Created by 杜建璋 on 2024/7/13.
//

#ifndef MPC_PACKAGE_MULTIPLICATIONSHAREEXECUTOR_H
#define MPC_PACKAGE_MULTIPLICATIONSHAREEXECUTOR_H
#include "../../../executor/Executor.h"

class MultiplicationShareExecutor : public Executor {
public:
    static const std::string BM_TAG;
protected:
    // benchmark
    int64_t _otRsaGenerationTime{};
    int64_t _otRsaEncryptionTime{};
    int64_t _otRsaDecryptionTime{};
    int64_t _otEntireComputationTime{};
    // hold
    int64_t _x{};
    // parts
    // _x = _x0 + _x1
    // y = _y0 + yb
    int64_t _x0{};
    int64_t _x1{};
    // MT
    // _a0, _b0, _c0 belongs to Alice
    // c = (_c0 + c1) = a * b = (_a0 + a1) * (_b0 + b1)
    int _l{};
    int64_t _a0{};
    int64_t _b0{};
    int64_t _c0{};
    int64_t _u0{};
    int64_t _v0{};

public:
    MultiplicationShareExecutor(int64_t x, int l);
    void compute() override;

protected:
    virtual void obtainMultiplicationTriple();

private:
    void process();
    void generateRandoms();
    void computeU();
    void computeV();
    void computeMix(int sender, int64_t &mix);
    void computeC();
    [[nodiscard]] int64_t corr(int i, int64_t x) const;
};


#endif //MPC_PACKAGE_MULTIPLICATIONSHAREEXECUTOR_H
