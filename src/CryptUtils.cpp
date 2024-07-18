//
// Created by 杜建璋 on 2024/7/18.
//

#include "utils/CryptUtils.h"
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

// copilot
void CryptUtils::generateRsaKeys(int bits, std::string &publicKey, std::string &privateKey) {
    RSA *rsa = RSA_generate_key(bits, RSA_F4, nullptr, nullptr);
    BIO *pri = BIO_new(BIO_s_mem());
    BIO *pub = BIO_new(BIO_s_mem());

    PEM_write_bio_RSAPrivateKey(pri, rsa, nullptr, nullptr, 0, nullptr, nullptr);
    PEM_write_bio_RSA_PUBKEY(pub, rsa);

    size_t pri_len = BIO_pending(pri);
    size_t pub_len = BIO_pending(pub);

    char *pri_key = (char *)malloc(pri_len + 1);
    char *pub_key = (char *)malloc(pub_len + 1);

    BIO_read(pri, pri_key, pri_len);
    BIO_read(pub, pub_key, pub_len);

    pri_key[pri_len] = '\0';
    pub_key[pub_len] = '\0';

    privateKey = std::string(pri_key);
    publicKey = std::string(pub_key);

    RSA_free(rsa);
    BIO_free_all(pub);
    BIO_free_all(pri);
    free(pri_key);
    free(pub_key);
}

// copilot
std::string CryptUtils::rsaEncrypt(const std::string &data, const std::string &publicKey) {
    RSA *rsa = RSA_new();
    BIO *keybio = BIO_new_mem_buf((void *)publicKey.c_str(), -1);
    PEM_read_bio_RSA_PUBKEY(keybio, &rsa, nullptr, nullptr);

    int len = RSA_size(rsa);
    char *encrypted = (char *)malloc(len);
    int result = RSA_public_encrypt(data.size(), (unsigned char *)data.c_str(), (unsigned char *)encrypted, rsa, RSA_PKCS1_PADDING);

    std::string encryptedStr;
    if (result >= 0) {
        encryptedStr = std::string(encrypted, result);
    }

    free(encrypted);
    BIO_free_all(keybio);
    RSA_free(rsa);

    return encryptedStr;

}

// copilot
std::string CryptUtils::rsaDecrypt(const std::string &encryptedData, const std::string &privateKey) {
    RSA *rsa = RSA_new();
    BIO *keybio = BIO_new_mem_buf((void *)privateKey.c_str(), -1);
    PEM_read_bio_RSAPrivateKey(keybio, &rsa, nullptr, nullptr);

    int len = RSA_size(rsa);
    char *decrypted = (char *)malloc(len);
    int result = RSA_private_decrypt(encryptedData.size(), (unsigned char *)encryptedData.c_str(), (unsigned char *)decrypted, rsa, RSA_PKCS1_PADDING);

    std::string decryptedStr;
    if (result >= 0) {
        decryptedStr = std::string(decrypted, result);
    }

    free(decrypted);
    BIO_free_all(keybio);
    RSA_free(rsa);

    return decryptedStr;
}
