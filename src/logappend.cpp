// #include "../include/logappend.h"
// #include "../include/input_validation.h"
// #include "../include/cryptography.h" 
// #include <iostream>
// #include <fstream>

// // Function to append log entry
// void logappend(const std::string& entry, const std::string& user_id, const std::string& room_id) {
//     // Validate room ID using the isValidRoomId function
//     if (!isValidRoomId(room_id)) {
//         std::cerr << "Invalid room ID format. Room ID must be numeric and not start with zero." << std::endl;
//         return;
//     }

//     std::ofstream logFile("log.txt", std::ios::app);  // Open log file in append mode
//     if (!logFile.is_open()) {
//         std::cerr << "Error: Could not open log file for writing." << std::endl;
//         return;
//     }

//     // If the room ID is valid, proceed with appending the log entry
//     logFile << "Entry: " << entry << ", User: " << user_id << ", Room: " << room_id << std::endl;

//     logFile.close();  // Close the log file

//     std::cout << "Log appended successfully." << std::endl;

//     // Generate a token for the entry (you can replace this with your token generation logic)
//     std::string token = generateToken(user_id + room_id);
//     // std::cout << "Generated Token: " << token << std::endl;
// }


#include "../include/logappend.h"
#include "../include/input_validation.h"
#include "../include/cryptography.h"  // Ensure this is included
#include "../include/output_encoding.h"
#include <iostream>
#include <fstream>
#include <ctime>


void logappend(const std::string& entry, const std::string& user_id, const std::string& room_id) {
    // Validate inputs
    if (!isValidRoomId(room_id)) {
        std::cerr << "Invalid room ID format. Room ID must be numeric and not start with zero." << std::endl;
        return;
    }
    if (!isValidUserId(user_id)) {
        std::cerr << "Invalid user ID format. User ID must be 5–10 alphanumeric characters or underscores." << std::endl;
        return;
    }

    // Open log file
    std::ofstream logFile("log.txt", std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Error: Could not open log file for writing." << std::endl;
        return;
    }

    // Encode sensitive data
    std::string encodedEntry = encodeOutput(entry);
    std::string encodedUserId = encodeOutput(user_id);
    std::string encodedRoomId = encodeOutput(room_id);

    // Add a timestamp
    std::time_t now = std::time(nullptr);
    char timestamp[20];
    std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

    // Generate a tamper-proof signature
    std::string data = encodedEntry + encodedUserId + encodedRoomId + timestamp;
    std::string signature = generateToken(data);

    // Append log entry with the signature
    logFile << "Timestamp: " << timestamp
            << ", Entry: " << encodedEntry
            << ", User: " << encodedUserId
            << ", Room: " << encodedRoomId
            << ", Signature: " << signature << std::endl;

    logFile.close();
    std::cout << "Log appended successfully." << std::endl;
}

