#include "../include/cryptography.h"
#include <cassert>
#include <iostream>
#include <cstdlib>  // For std::getenv

void testCryptography() {
    // Check if SECRET_KEY is set
    const char* secretKey = std::getenv("SECRET_KEY");
    if (!secretKey) {
        std::cerr << "Error: SECRET_KEY environment variable not set!" << std::endl;
        return;
    }

    // Test token generation
    std::string token1 = generateToken("user1room101");
    std::string token2 = generateToken("user2room202");

    // Ensure tokens are consistent
    assert(token1 == generateToken("user1room101"));
    assert(token2 == generateToken("user2room202"));

    // Ensure tokens are unique for different data
    assert(token1 != token2);

    std::cout << "All cryptography tests passed!" << std::endl;
}

int main() {
    testCryptography();
    return 0;
}
