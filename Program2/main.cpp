#include <iostream>
#include <cxxopts.hpp>
#include <optional>
#include <masesk/EasySocket.hpp>
#include "crypto.hpp"

unsigned char *key;

std::optional<std::string> ParseArgs(int argc, char *argv[]) {
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

    return key;
}

void handleData(const std::string &data) {

    unsigned char plaintext[128];
    const auto plaintext_str = spideroak_crypto::decrypt((unsigned char *)data.c_str(),
        data.size(),
        key);

    std::cout << "Successful! Decrypted the following message:\n\n" << plaintext_str << std::endl;
}

int main(int argc, char *argv[]) {
    const auto key_arg = ParseArgs(argc, argv);

    if (key_arg.has_value()) {

        key = (unsigned char *)key_arg.value().c_str();

        masesk::EasySocket socketManager;
        socketManager.socketListen("spideroak_exercise", 8080, &handleData);
        return 0;
    } else {
        std::cerr << "Invalid arguments." << std::endl;
        return EXIT_FAILURE;
    }
}
