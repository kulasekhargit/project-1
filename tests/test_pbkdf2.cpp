#include "../include/cryptography.h"
#include <iostream>
#include <cassert>

void testPBKDF2() {
    std::string password = "TestPassword123";
    std::string salt = generateSalt();

    int iterations = 1000;
    int dkLen = 32;

    std::string hash1 = pbkdf2(password, salt, iterations, dkLen);
    std::string hash2 = pbkdf2(password, salt, iterations, dkLen);

    // Test if the same password and salt produce the same hash
    assert(hash1 == hash2);

    std::string anotherHash = pbkdf2("AnotherPassword456", salt, iterations, dkLen);

    // Test if different passwords produce different hashes
    assert(hash1 != anotherHash);

    std::cout << "PBKDF2 tests passed successfully!" << std::endl;
}

int main() {
    testPBKDF2();
    return 0;
}
