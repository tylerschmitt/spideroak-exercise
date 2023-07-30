
namespace spideroak_crypto {
    // Adapted from: https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption
    std::string encrypt(unsigned char *key, unsigned char *plaintext, size_t plaintext_len);
    std::string decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key);
}