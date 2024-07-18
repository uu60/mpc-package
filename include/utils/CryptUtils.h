//
// Created by 杜建璋 on 2024/7/18.
//

#ifndef MPC_PACKAGE_CRYPTUTILS_H
#define MPC_PACKAGE_CRYPTUTILS_H
#include <iostream>

class CryptUtils {
public:
    static void generateRsaKeys(int bits, std::string &publicKey, std::string &privateKey);
    static std::string rsaEncrypt(const std::string &data, const std::string &publicKey);
    static std::string rsaDecrypt(const std::string &encryptedData, const std::string &privateKey);
};


#endif //MPC_PACKAGE_CRYPTUTILS_H
