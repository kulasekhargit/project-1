#include "../include/logread.h"
#include "../include/cryptography.h"
#include "../include/output_encoding.h"
#include "../include/input_validation.h"

#include <iostream>
#include <fstream>
#include <string>

void logread(const std::string& user_id) {
    // Validate user ID
    if (!isValidUserId(user_id)) {
        std::cerr << "Error: Invalid user ID format." << std::endl;
        return;
    }

    // Open log file
    std::ifstream logFile("log.txt");
    if (!logFile.is_open()) {
        std::cerr << "Error: Could not open the log file." << std::endl;
        return;
    }

    std::string sanitizedUserId = encodeOutput(user_id);  // Encode the user ID for safe matching
    std::string line;
    bool found = false;

    while (std::getline(logFile, line)) {
        // Match encoded user ID
        if (line.find("User: " + sanitizedUserId + ",") != std::string::npos) {
            std::cout << line << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "No log entries found for user: " << sanitizedUserId << std::endl;
    }

    logFile.close();
}
