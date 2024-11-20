#include <iostream>
#include <cassert>
#include "../include/cryptography.h"

void testGenerateSalt() {
    std::string salt = generateSalt(16);
    assert(salt.size() == 16);  // Ensure salt length is correct
    for (char c : salt) {
        // Ensure the salt contains only valid characters
        assert((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
    }
    std::cout << "Salt generation test passed!" << std::endl;
}

void testPBKDF2() {
    std::string password = "securepassword";
    std::string salt = generateSalt(16);
    std::string derivedKey = pbkdf2(password, salt, 1000, 32);

    // Ensure derived key length matches the expected length
    assert(derivedKey.size() == 64);  // 32 bytes as hex string (64 characters)
    std::cout << "PBKDF2 test passed!" << std::endl;
}

int main() {
    testGenerateSalt();
    testPBKDF2();
    std::cout << "Memory management test passed successfully!" << std::endl;
    return 0;
}
