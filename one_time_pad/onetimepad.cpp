// CSC 116: Assignment 1
// Jason Thomo (V00949336)
#include <iostream>
#include <string>

std::string one_time_pad(std::string key, std::string message) {
    std::string encrypted {};
    for (size_t i=0; i < message.size(); i++) {
        char c = message.at(i) ^ key.at(i);
        encrypted += c;
    }
    return encrypted;
}

std::string process_encrypted(std::string encrypted) {
    std::string processed {};
    for (auto c : encrypted) {
        if (int(c) < 32 || int(c) > 126)
            processed += "("+ std::to_string(int(c)) +")";
        else
            processed += c;
    }
    return processed;
}

int main() {
    std::string key {};
    std::getline(std::cin, key);
    std::cout << "Original key [" << key << "]" << std::endl;

    std::string message {};
    while (std::getline(std::cin, message)) {
        std::cout << "Original message [" << message << "]" << std::endl;
        if (message.length() > key.length()) {
            std::cout << "Error: the length of the key [" << key.length() << "] is smaller than the length of the message to encrypt [" << message.length() << "]" << std::endl;
            exit(1);
        }
        std::cout << "Encrypted [" << process_encrypted(one_time_pad(key, message)) << "]" << std::endl;
        std::cout << "Decrypted [" << one_time_pad(key, one_time_pad(key, message)) << "]" << std::endl;
    }
    return 0;
}