#include <cxxopts.hpp>
#include <iostream>
#include <optional>
#include <masesk/EasySocket.hpp>
#include "crypto.hpp"


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

int main(int argc, char *argv[]) {
    const auto key_and_plaintext = ParseArgs(argc, argv);

    if (key_and_plaintext.key.has_value() && key_and_plaintext.plaintext.has_value()) {

        const auto ciphertext_packet = spideroak_crypto::encrypt(
            (unsigned char *)key_and_plaintext.key.value().c_str(),
            (unsigned char *)key_and_plaintext.plaintext.value().c_str(),
            key_and_plaintext.plaintext.value().size());

        if (ciphertext_packet.success && ciphertext_packet.crypto_str.has_value()) {
            masesk::EasySocket socketManager;
            socketManager.socketConnect("spideroak_exercise", "127.0.0.1", 8080);
            socketManager.socketSend("spideroak_exercise", ciphertext_packet.crypto_str.value());
            socketManager.closeConnection("spideroak_exercise");
        } else {
            std::cout << "Encryption failed!" << std::endl;;
        }

        return 0;
    } else {
        std::cerr << "Invalid arguments." << std::endl;
        return EXIT_FAILURE;
    }
}
