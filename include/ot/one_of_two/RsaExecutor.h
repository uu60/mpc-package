//
// Created by 杜建璋 on 2024/7/15.
//

#ifndef MPC_PACKAGE_RSAEXECUTOR_H
#define MPC_PACKAGE_RSAEXECUTOR_H
#include <string>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/sha.h>

class RsaExecutor {
private:
    // RSA key bits
    int bits = 2048;
    // corresponding mpi rank
    int sender{};
    // params for sender
    int m0{};
    int m1{};
    int rand0{};
    int rand1{};
    std::string pri{};
    // params for receiver

    // params for both
    std::string pub{};

public:
    explicit RsaExecutor(int bits);
    void compute();
};


#endif //MPC_PACKAGE_RSAEXECUTOR_H
