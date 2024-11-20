#include "auth.h"
#include <iostream>

bool authenticateUser(const std::string& token) {
    if (token == "secure_token") {
        return true;
    } else {
        std::cerr << "Authentication failed." << std::endl;
        return false;
    }
}
