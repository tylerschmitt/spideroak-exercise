#include <iostream>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/err.h>

namespace spideroak_crypto {
    
    int encrypt(unsigned char * key, unsigned char * plaintext, size_t plaintext_len, unsigned char *ciphertext)
    {
        unsigned char *iv = (unsigned char *)"0123456789012345";

        EVP_CIPHER_CTX *ctx;

        int len;

        int ciphertext_len;

        /* Create and initialise the context */
        if(!(ctx = EVP_CIPHER_CTX_new()))
            std::cout << "error" << std::endl;

        /*
        * Initialise the encryption operation. IMPORTANT - ensure you use a key
        * and IV size appropriate for your cipher
        * In this example we are using 256 bit AES (i.e. a 256 bit key). The
        * IV size for *most* modes is the same as the block size. For AES this
        * is 128 bits
        */
        if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
            std::cout << "error" << std::endl;

        /*
        * Provide the message to be encrypted, and obtain the encrypted output.
        * EVP_EncryptUpdate can be called multiple times if necessary
        */
        if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
            std::cout << "error" << std::endl;
        ciphertext_len = len;

        /*
        * Finalise the encryption. Further ciphertext bytes may be written at
        * this stage.
        */
        if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
            std::cout << "error" << std::endl;
        ciphertext_len += len;

        /* Clean up */
        EVP_CIPHER_CTX_free(ctx);

        return ciphertext_len;
    }

}