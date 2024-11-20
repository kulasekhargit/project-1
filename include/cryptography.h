// #ifndef CRYPTOGRAPHY_H
// #define CRYPTOGRAPHY_H

// #include <string>

// std::string generateToken(const std::string& data);

// #endif


#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

#include <string>
#include <vector>

std::string generateToken(const std::string& data);
std::string generateSalt(size_t length = 16);
std::string pbkdf2(const std::string& password, const std::string& salt, int iterations, int dkLen);

#endif



