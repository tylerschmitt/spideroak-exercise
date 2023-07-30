#include <iostream>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <string.h>

#include "crypto.hpp"

namespace spideroak_crypto {
    
    void handleErrors(void)
    {
        ERR_print_errors_fp(stderr);
    }

    CryptoPacket encrypt(unsigned char *key, unsigned char *plaintext, size_t plaintext_len)
    {
        CryptoPacket packet = {};

        unsigned char ciphertext[128];
        unsigned char *iv = (unsigned char *)"0123456789012345";

        EVP_CIPHER_CTX *ctx;

        int len;

        int ciphertext_len;

        /* Create and initialise the context */
        if(!(ctx = EVP_CIPHER_CTX_new())) {
            return packet;
        }

        /*
        * Initialise the encryption operation. IMPORTANT - ensure you use a key
        * and IV size appropriate for your cipher
        * In this example we are using 256 bit AES (i.e. a 256 bit key). The
        * IV size for *most* modes is the same as the block size. For AES this
        * is 128 bits
        */
        if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
            return packet;
        }

        /*
        * Provide the message to be encrypted, and obtain the encrypted output.
        * EVP_EncryptUpdate can be called multiple times if necessary
        */
        if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len)) {
            return packet;
        }
        ciphertext_len = len;

        /*
        * Finalise the encryption. Further ciphertext bytes may be written at
        * this stage.
        */
        if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) {
            return packet;
        }
        ciphertext_len += len;

        /* Clean up */
        EVP_CIPHER_CTX_free(ctx);

        packet.success = true;
        packet.crypto_str = std::string(reinterpret_cast<char const*>(ciphertext), ciphertext_len);

        return packet;
    }

    CryptoPacket decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key)
    {
        CryptoPacket packet = {};

        unsigned char plaintext[128];
        unsigned char *iv = (unsigned char *)"0123456789012345";

        EVP_CIPHER_CTX *ctx;

        int len;

        int plaintext_len;

        /* Create and initialise the context */
        if(!(ctx = EVP_CIPHER_CTX_new())) {
            return packet;
        }

        /*
        * Initialise the decryption operation. IMPORTANT - ensure you use a key
        * and IV size appropriate for your cipher
        * In this example we are using 256 bit AES (i.e. a 256 bit key). The
        * IV size for *most* modes is the same as the block size. For AES this
        * is 128 bits
        */
        if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
            return packet;
        }

        /*
        * Provide the message to be decrypted, and obtain the plaintext output.
        * EVP_DecryptUpdate can be called multiple times if necessary.
        */
        if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len)) {
            return packet;
        }
        plaintext_len = len;

        /*
        * Finalise the decryption. Further plaintext bytes may be written at
        * this stage.
        */
        if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) {
            return packet;
        }
        plaintext_len += len;

        /* Clean up */
        EVP_CIPHER_CTX_free(ctx);

        packet.success = true;
        packet.crypto_str = std::string(reinterpret_cast<char const*>(plaintext), plaintext_len);

        return packet;
    }

}