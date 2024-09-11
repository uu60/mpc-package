//
// Created by 杜建璋 on 2024/7/6.
//

#ifndef MPC_PACKAGE_MATH_H
#define MPC_PACKAGE_MATH_H

#include <string>
#include <openssl/bn.h>
#include <openssl/evp.h>

class Math {
public:
    // generate a random
    static int rand32();
    static int rand32(int lowest, int highest);
    static int64_t rand64();
    static int64_t rand64(int64_t lowest, int64_t highest);
    static std::string rand0b(int bytes);
    static std::string rand0b(int lowBytes, int highBytes);
    // '1' + 1 = 49 + 1 = 50 = '2'
    static std::string add(const std::string &add0, int64_t add1);
    static std::string add(const std::string &add0, const std::string &add1);
    static std::string minus(const std::string &add0, const std::string &add1);
    // dividend % divisor
    // divisor should be positive
    static int64_t ring(int64_t num, int l);
    // constraint l
    static int realL(int l);
private:
    // str as binary to bignum. "1" -> 49
    static BIGNUM *bignum(const std::string& str);
    static BIGNUM *bignum(const std::string& str, bool positive);
    // bignum as binary to str. 49 -> 1
    static std::string string(BIGNUM* bn);
    static BIGNUM *add(BIGNUM* add0, int64_t add1);
    static std::string add(const std::string &add0, const std::string &add1, bool minus);
};


#endif //MPC_PACKAGE_MATH_H
