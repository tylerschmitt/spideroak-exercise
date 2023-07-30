#include <gtest/gtest.h>
#include "crypto.hpp"

TEST(CryptoTest, BasicEncryptDecryptTest) {
    const std::string key = "40baaed112a2fdc0934055fd625f906a4a21a07c6aaf45de691b4f6962f10b88";
    const std::string plaintext = "Test message!";

    const auto ciphertext = spideroak_crypto::encrypt(
      (unsigned char *)key.c_str(),
      (unsigned char *)plaintext.c_str(),
      plaintext.size());

    const auto plaintext_out = spideroak_crypto::decrypt(
      (unsigned char *)ciphertext.c_str(),
      ciphertext.size(),
      (unsigned char *)key.c_str());

      ASSERT_EQ(plaintext, plaintext_out);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}