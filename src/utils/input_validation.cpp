// #include "../../include/input_validation.h"
// #include <regex>

// // Function to validate general input (alphanumeric and underscores only)
// bool isValidInput(const std::string& input) {
//     std::regex validPattern("^[a-zA-Z0-9_]*$"); // Allows only alphanumeric characters and underscores
//     return std::regex_match(input, validPattern);
// }

// // Function to validate user ID (5-10 alphanumeric characters)
// bool isValidUserId(const std::string& user_id) {
//     std::regex validPattern("^[a-zA-Z]*[1-9][0-9]{2,4}$"); // Alphanumeric with numbers, no leading zero for digits
//  // Alphanumeric, 5-10 characters
//     return std::regex_match(user_id, validPattern);
// }

// // Function to validate room ID (3-5 characters, alphanumeric, with possible letters or numbers)
// bool isValidRoomId(const std::string& room_id) {
//     // Allowing both alphanumeric characters (letters and digits), with an optional leading string and ending numeric part
//     std::regex validPattern("^[a-zA-Z]*[0-9]{3,5}$"); // Alphanumeric (letters and numbers), 3-5 characters (letters may precede numbers)
//     return std::regex_match(room_id, validPattern);
// }

#include "../../include/input_validation.h"
#include <regex>

// Function to validate general input (alphanumeric and underscores only)
bool isValidInput(const std::string& input) {
    std::regex validPattern("^[a-zA-Z0-9_]*$"); // Allows only alphanumeric characters and underscores
    return std::regex_match(input, validPattern);
}

// Function to validate user ID (5-10 alphanumeric characters or underscores)
bool isValidUserId(const std::string& user_id) {
    // Alphanumeric, underscores, and length between 5 and 10 characters
    std::regex validPattern("^[a-zA-Z0-9_]{5,10}$");
    return std::regex_match(user_id, validPattern);
}

// Function to validate room ID (3-5 characters, alphanumeric, with no leading zeros)
bool isValidRoomId(const std::string& room_id) {
    // Allow alphanumeric with optional letters, but numbers cannot start with zero
    std::regex validPattern("^[a-zA-Z]*[1-9][0-9]{2,4}$");
    return std::regex_match(room_id, validPattern);
}
