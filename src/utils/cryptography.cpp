// #include "../../libbcrypt/include/bcrypt/BCrypt.hpp"
// #include "../../include/cryptography.h"
// #include "../../include/picosha2.h"  // Include PicoSHA2 for SHA-256 hashing
// #include <cstdlib>      // For getenv
// #include <iostream>     // For error message if key is missing
// #include <sstream>
// #include <iomanip>

// // Function to generate a secure token using SHA-256 and the secret key
// std::string generateToken(const std::string& data) {
//     // Get the secret key from the environment variable
//     const char* key = std::getenv("SECRET_KEY");
//     if (key == nullptr) {
//         std::cerr << "Error: SECRET_KEY environment variable not set!" << std::endl;
//         return "";
//     }

//     // Combine the secret key with the input data
//     std::string message = std::string(key) + data;

//     // Generate the SHA-256 hash of the combined message
//     std::string hash_hex_str;
//     picosha2::hash256_hex_string(message, hash_hex_str);  // Generate SHA-256 hash in hex format

//     return hash_hex_str;
// }


#include "../../include/cryptography.h"
#include "../../include/picosha2.h"  // For SHA-256 hashing
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <random>  // For secure random salt generation

// Function to generate a secure random salt using strncpy
std::string generateSalt(size_t length) {
    static const char charset[] =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char saltBuffer[256];  // Buffer to hold the salt
    std::random_device rd;  // Secure random number generator
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> dist(0, sizeof(charset) - 2);

    for (size_t i = 0; i < length && i < sizeof(saltBuffer) - 1; i++) {
        saltBuffer[i] = charset[dist(generator)];
    }

    // Null-terminate the string
    saltBuffer[length] = '\0';

    // Safely copy the buffer into a std::string
    std::string salt;
    strncpy(saltBuffer, saltBuffer, length);
    salt = std::string(saltBuffer);

    return salt;
}

// Function to perform HMAC-SHA256
std::vector<uint8_t> hmacSHA256(const std::string& key, const std::string& data) {
    const size_t blockSize = 64;  // Block size for SHA-256
    std::vector<uint8_t> o_key_pad(blockSize, 0x5c);
    std::vector<uint8_t> i_key_pad(blockSize, 0x36);

    std::vector<uint8_t> keyBytes(key.begin(), key.end());

    if (keyBytes.size() > blockSize) {
        keyBytes.resize(32);  // SHA-256 output size
        picosha2::hash256(keyBytes, keyBytes);  // Hash the key if it's longer than block size
    }

    keyBytes.resize(blockSize, 0x00);

    for (size_t i = 0; i < blockSize; ++i) {
        o_key_pad[i] ^= keyBytes[i];
        i_key_pad[i] ^= keyBytes[i];
    }

    std::vector<uint8_t> innerHashInput = i_key_pad;
    innerHashInput.insert(innerHashInput.end(), data.begin(), data.end());

    std::vector<uint8_t> innerHash(32);
    picosha2::hash256(innerHashInput, innerHash);  // Hash the inner padded data

    std::vector<uint8_t> outerHashInput = o_key_pad;
    outerHashInput.insert(outerHashInput.end(), innerHash.begin(), innerHash.end());

    std::vector<uint8_t> outerHash(32);
    picosha2::hash256(outerHashInput, outerHash);  // Final HMAC result

    return outerHash;
}

// PBKDF2 implementation
std::string pbkdf2(const std::string& password, const std::string& salt, int iterations, int dkLen) {
    int hLen = 32;  // Output length of HMAC-SHA256
    int l = (dkLen + hLen - 1) / hLen;
    int r = dkLen - (l - 1) * hLen;

    std::vector<uint8_t> derivedKey;

    for (int i = 1; i <= l; i++) {
        // Salt with counter (big-endian representation)
        std::string saltWithCounter = salt + std::string(reinterpret_cast<const char*>(&i), 4);
        std::vector<uint8_t> u = hmacSHA256(password, saltWithCounter);

        std::vector<uint8_t> t = u;

        for (int j = 1; j < iterations; j++) {
            u = hmacSHA256(password, std::string(u.begin(), u.end()));
            std::transform(t.begin(), t.end(), u.begin(), t.begin(), std::bit_xor<>());
        }

        derivedKey.insert(derivedKey.end(), t.begin(), (i == l ? t.begin() + r : t.end()));
    }

    // Convert the derived key to a hex string
    std::ostringstream oss;
    for (uint8_t byte : derivedKey) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }

    return oss.str();
}

std::string generateToken(const std::string& data) {
    const char* key = std::getenv("SECRET_KEY");
    if (!key) {
        std::cerr << "Error: SECRET_KEY environment variable not set!" << std::endl;
        return "";
    }
    std::string combined = std::string(key) + data;
    std::string hash;
    picosha2::hash256_hex_string(combined, hash);
    return hash;
}

