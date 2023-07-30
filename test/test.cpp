#include <gtest/gtest.h>
#include "crypto.hpp"

TEST(CryptoTest, BasicEncryptDecryptTest) {
    const std::string key = "40baaed112a2fdc0934055fd625f906a4a21a07c6aaf45de691b4f6962f10b88";
    const std::string plaintext = "Test message!";

    const auto cipher_packet = spideroak_crypto::encrypt(
      (unsigned char *)key.c_str(),
      (unsigned char *)plaintext.c_str(),
      plaintext.size());

    ASSERT_TRUE(cipher_packet.success);

    const auto plaintext_packet = spideroak_crypto::decrypt(
      (unsigned char *)cipher_packet.crypto_str.value().c_str(),
      cipher_packet.crypto_str.value().size(),
      (unsigned char *)key.c_str());

    ASSERT_TRUE(cipher_packet.success);
    ASSERT_TRUE(plaintext_packet.crypto_str.has_value());
    ASSERT_EQ(plaintext, plaintext_packet.crypto_str.value());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}