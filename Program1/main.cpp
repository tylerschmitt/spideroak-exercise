
#include <cxxopts.hpp>
#include <iostream>
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

// Adapted from: https://stackoverflow.com/questions/73631293/how-to-encrypt-a-string-using-openssl-c-library-and-a-public-key-file
std::string EncryptMessage(const KeyAndPlaintext key_msg) {
    return ""; // add exception/error handling
}

int main(int argc, char *argv[]) {
    const auto key_and_plaintext = ParseArgs(argc, argv);

    if (key_and_plaintext.key.has_value() && key_and_plaintext.plaintext.has_value()) {

        const auto encrypted_msg = EncryptMessage(key_and_plaintext);

        return 0;
    } else {
        std::cerr << "Invalid arguments." << std::endl;
        return EXIT_FAILURE;
    }
}
