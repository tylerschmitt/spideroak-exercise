#include <iostream>
#include <cxxopts.hpp>
#include <optional>

struct KeyAndMessage {
    std::optional<std::string> key;
    std::optional<std::string> message;
};

KeyAndMessage ParseArgs(int argc, char *argv[]) {
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

    std::optional<std::string> message = std::nullopt;
    if (result.count("message")) {
      message = result["message"].as<std::string>();
    } else {
        std::cerr << "No message argument!" << std::endl;
    }

    return KeyAndMessage{key, message};
}

int main(int argc, char *argv[]) {
    const auto key_and_message = ParseArgs(argc, argv);

    if (key_and_message.key.has_value() && key_and_message.message.has_value()) {
        std::cout << key_and_message.key.value() << std::endl;
        std::cout << key_and_message.message.value() << std::endl;
        return 0;
    } else {
        std::cerr << "Invalid arguments." << std::endl;
        return EXIT_FAILURE;
    }
}
