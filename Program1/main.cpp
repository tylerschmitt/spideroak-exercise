#include <cxxopts.hpp>
#include <iostream>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <optional>


struct KeyAndPlaintext {
    std::optional<std::string> key;
    std::optional<std::string> plaintext;
};



KeyAndPlaintext ParseArgs(int argc, char *argv[]) {
    cxxopts::Options options("Program1", "Encrypt and send message to Program2.");

    options.add_options()
    ("k,key", "Key to encrypt message", cxxopts::value<std::string>())
    ("m,message", "Message to encrypt", cxxopts::value<std::string>())
    ;

    auto result = options.parse(argc, argv);

    std::optional<std::string> key = std::nullopt;
    if (result.count("key")) {
      key = result["key"].as<std::string>();
    } else {
        std::cerr << "No key argument!" << std::endl;
    }

    std::optional<std::string> plaintext = std::nullopt;
    if (result.count("message")) {
      plaintext = result["message"].as<std::string>();
    } else {
        std::cerr << "No message argument!" << std::endl;
    }

    return KeyAndPlaintext{key, plaintext};
}

int encrypt(std::string keyString, std::string plaintextString, unsigned char *ciphertext)
{
    unsigned char *key = (unsigned char *)keyString.c_str();
    unsigned char *plaintext = (unsigned char *)plaintextString.c_str();
    unsigned char *iv = (unsigned char *)"0123456789012345";

    size_t plaintext_len = plaintextString.size();

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

int main(int argc, char *argv[]) {
    const auto key_and_plaintext = ParseArgs(argc, argv);

    if (key_and_plaintext.key.has_value() && key_and_plaintext.plaintext.has_value()) {

        unsigned char ciphertext[128];

        const auto ciphertext_len = encrypt(
            key_and_plaintext.key.value(),
            key_and_plaintext.plaintext.value(),
            ciphertext);

        return 0;
    } else {
        std::cerr << "Invalid arguments." << std::endl;
        return EXIT_FAILURE;
    }
}
