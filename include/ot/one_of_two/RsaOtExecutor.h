//
// Created by 杜建璋 on 2024/7/15.
//

#ifndef MPC_PACKAGE_RSAOTEXECUTOR_H
#define MPC_PACKAGE_RSAOTEXECUTOR_H
#include <string>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/sha.h>

// according to https://blog.csdn.net/qq_16763983/article/details/128055146
class RsaOtExecutor {
private:
    // RSA key _bits
    int _bits{};
    // correspond mpi rank
    bool _isSender{};
    // params for sender
    std::string _rand0{};
    std::string _rand1{};
    std::string _pri{};

    // params for receiver
    std::string _randK{};
    int _i; // msg choice

    // params for both
    std::string _pub{};
    int64_t _m0{};
    int64_t _m1{};

public:
    // _m0 and _m1 are for sender (invalid for receiver)
    // i is for receiver (invalid for sender)
    explicit RsaOtExecutor(int sender, int64_t m0, int64_t m1, int i);
    explicit RsaOtExecutor(int bits, int sender, int64_t m0, int64_t m1, int i);
    void compute();
    int64_t result();

private:
    // methods for sender
    void generateAndShareRsaKeys();
    void generateAndShareRandoms();

    // methods for receiver

    // methods for both
    void process();
};


#endif //MPC_PACKAGE_RSAOTEXECUTOR_H
