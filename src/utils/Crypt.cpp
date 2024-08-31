//
// Created by 杜建璋 on 2024/7/18.
//

#include "utils/Crypt.h"
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <vector>
#include <string>

// copilot
void Crypt::generateRsaKeys(int bits, std::string &publicKey, std::string &privateKey) {
    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, nullptr);
    EVP_PKEY *pkey = nullptr;

    if (!ctx || EVP_PKEY_keygen_init(ctx) <= 0 || EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, bits) <= 0 || EVP_PKEY_keygen(ctx, &pkey) <= 0) {
        // Handle errors
        if (ctx) EVP_PKEY_CTX_free(ctx);
        return;
    }

    BIO *pri = BIO_new(BIO_s_mem());
    BIO *pub = BIO_new(BIO_s_mem());

    PEM_write_bio_PrivateKey(pri, pkey, nullptr, nullptr, 0, nullptr, nullptr);
    PEM_write_bio_PUBKEY(pub, pkey);

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

    EVP_PKEY_free(pkey);
    BIO_free_all(pub);
    BIO_free_all(pri);
    free(pri_key);
    free(pub_key);
}

// copilot
std::string Crypt::rsaEncrypt(const std::string &data, const std::string &publicKey) {
    EVP_PKEY *pkey = nullptr;
    EVP_PKEY_CTX *ctx = nullptr;
    BIO *keybio = BIO_new_mem_buf((void *)publicKey.c_str(), -1);
    pkey = PEM_read_bio_PUBKEY(keybio, nullptr, nullptr, nullptr);

    if (!pkey) {
        BIO_free(keybio);
        throw std::runtime_error("Failed to read public key");
    }

    ctx = EVP_PKEY_CTX_new(pkey, nullptr);
    if (!ctx) {
        EVP_PKEY_free(pkey);
        BIO_free(keybio);
        throw std::runtime_error("Failed to create context");
    }

    if (EVP_PKEY_encrypt_init(ctx) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(pkey);
        BIO_free(keybio);
        throw std::runtime_error("Failed to initialize encryption");
    }

    size_t outlen;
    if (EVP_PKEY_encrypt(ctx, nullptr, &outlen, (unsigned char *)data.c_str(), data.size()) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(pkey);
        BIO_free(keybio);
        throw std::runtime_error("Failed to determine buffer length");
    }

    std::vector<unsigned char> outbuf(outlen);
    if (EVP_PKEY_encrypt(ctx, outbuf.data(), &outlen, (unsigned char *)data.c_str(), data.size()) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(pkey);
        BIO_free(keybio);
        throw std::runtime_error("Encryption failed");
    }

    EVP_PKEY_CTX_free(ctx);
    EVP_PKEY_free(pkey);
    BIO_free(keybio);

    return std::string(outbuf.begin(), outbuf.end());
}

// copilot
std::string Crypt::rsaDecrypt(const std::string &encryptedData, const std::string &privateKey) {
    EVP_PKEY *pkey = nullptr;
    EVP_PKEY_CTX *ctx = nullptr;
    BIO *keybio = BIO_new_mem_buf((void *)privateKey.c_str(), -1);
    pkey = PEM_read_bio_PrivateKey(keybio, nullptr, nullptr, nullptr);

    if (!pkey) {
        BIO_free(keybio);
        throw std::runtime_error("Failed to read private key");
    }

    ctx = EVP_PKEY_CTX_new(pkey, nullptr);
    if (!ctx) {
        EVP_PKEY_free(pkey);
        BIO_free(keybio);
        throw std::runtime_error("Failed to create context");
    }

    if (EVP_PKEY_decrypt_init(ctx) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(pkey);
        BIO_free(keybio);
        throw std::runtime_error("Failed to initialize decryption");
    }

    size_t outlen;
    if (EVP_PKEY_decrypt(ctx, nullptr, &outlen, (unsigned char *)encryptedData.c_str(), encryptedData.size()) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(pkey);
        BIO_free(keybio);
        throw std::runtime_error("Failed to determine buffer length");
    }

    std::string decryptedStr(outlen, '\0');
    if (EVP_PKEY_decrypt(ctx, (unsigned char *)decryptedStr.data(), &outlen, (unsigned char *)encryptedData.c_str(), encryptedData.size()) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(pkey);
        BIO_free(keybio);
        throw std::runtime_error("Decryption failed");
    }

    decryptedStr.resize(outlen);

    EVP_PKEY_CTX_free(ctx);
    EVP_PKEY_free(pkey);
    BIO_free(keybio);

    return decryptedStr;
}


