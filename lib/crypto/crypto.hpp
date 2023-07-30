#include <optional>

namespace spideroak_crypto {

    struct CryptoPacket {
        bool success = false;
        std::optional<std::string> crypto_str = std::nullopt;
    };

    // Adapted from: https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption
    CryptoPacket encrypt(unsigned char *key, unsigned char *plaintext, size_t plaintext_len);
    CryptoPacket decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key);
}