//
// Created by 杜建璋 on 2024/7/15.
//

#include <utility>

#include "ot/one_of_two/RsaExecutor.h"
#include "utils/MpiUtils.h"
#include "utils/MathUtils.h"
#include "utils/CryptUtils.h"
#include "utils/Log.h"

RsaExecutor::RsaExecutor(int sender, int64_t m0, int64_t m1, int i)
        : RsaExecutor(2048, sender, m0, m1, i) {
}

RsaExecutor::RsaExecutor(int bits, int sender, int64_t m0, int64_t m1, int i) {
    _bits = bits;
    _isSender = sender == MpiUtils::getMpiRank();
    if (_isSender) {
        _m0 = m0;
        _m1 = m1;
    } else {
        _i = i;
    }
}

void RsaExecutor::compute() {
    // preparation
    generateAndShareRandoms();
    generateAndShareRsaKeys();

    // process
    process();
}

void RsaExecutor::generateAndShareRsaKeys() {
    if (_isSender) {
        CryptUtils::generateRsaKeys(_bits, _pub, _pri);
        MpiUtils::send(&_pub);
    } else {
        MpiUtils::recv(&_pub);
    }
}

void RsaExecutor::generateAndShareRandoms() {
    // 11 for PKCS#1 v1.5 padding
    int maxLen = (_bits >> 3) - 11;
    if (_isSender) {
        _rand0 = MathUtils::rand0b(1, maxLen);
        _rand1 = MathUtils::rand0b(1, maxLen);
        MpiUtils::send(&_rand0);
        MpiUtils::send(&_rand1);
    } else {
        _randK = MathUtils::rand0b(1, maxLen);
        MpiUtils::recv(&_rand0);
        MpiUtils::recv(&_rand1);
    }
}

void RsaExecutor::process() {
    if (!_isSender) {
        std::string ek = CryptUtils::rsaEncrypt(_randK, _pub);
//        Log::d(ek);
        std::string sumStr = MathUtils::add(ek, _i == 0 ? _rand0 : _rand1);
        MpiUtils::send(&sumStr);

        std::string m0, m1;
        MpiUtils::recv(&m0);
        MpiUtils::recv(&m1);

        int64_t m = std::stoll(MathUtils::minus(_i == 0 ? m0 : m1, _randK));
        (_i == 0 ? _m0 : _m1) = m;
    } else {
        std::string sumStr;
        MpiUtils::recv(&sumStr);
//        Log::d(sumStr);
        std::string k0 = CryptUtils::rsaDecrypt(
                MathUtils::minus(sumStr, _rand0), _pri
        );
        std::string k1 = CryptUtils::rsaDecrypt(
                MathUtils::minus(sumStr, _rand1), _pri
        );
        std::string m0 = MathUtils::add(std::to_string(_m0), k0);
        std::string m1 = MathUtils::add(std::to_string(_m1), k1);
        MpiUtils::send(&m0);
        MpiUtils::send(&m1);
    }
}

int64_t RsaExecutor::result() {
    return _i == 0 ? _m0 : _m1;
}
