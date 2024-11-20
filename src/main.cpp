// #include "../include/auth.h"
// #include "../include/logappend.h"
// #include "../include/logread.h"
// #include "../include/input_validation.h"
// #include <iostream>

// int main(int argc, char* argv[]) {
//     if (argc < 2) {
//         std::cerr << "Usage: secure_logging.exe <command> [options]" << std::endl;
//         return 1;
//     }

//     std::string command = argv[1];
    
//     if (command == "logappend") {
//         if (argc < 5) {
//             std::cerr << "Usage: secure_logging.exe logappend entry user_id room_id" << std::endl;
//             return 1;
//         }
//         if (isValidUserId(argv[3]) && isValidRoomId(argv[4])) {
//             logappend(argv[2], argv[3], argv[4]);
//         } else {
//             std::cerr << "Invalid user ID or room ID." << std::endl;
//             return 1;
//         }
//     } else if (command == "logread") {
//         if (argc < 3) {
//             std::cerr << "Usage: secure_logging.exe logread user_id" << std::endl;
//             return 1;
//         }
//         logread(argv[2]);
//     } else {
//         std::cerr << "Unknown command: " << command << std::endl;
//         return 1;
//     }

//     return 0;
// }

#include "../include/auth.h"
#include "../include/logappend.h"
#include "../include/logread.h"
#include "../include/input_validation.h"
#include "../include/cryptography.h"  // Include cryptography for token generation
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: secure_logging.exe <command> [options]" << std::endl;
        return 1;
    }

    std::string command = argv[1];
    
    if (command == "logappend") {
        if (argc < 5) {
            std::cerr << "Usage: secure_logging.exe logappend entry user_id room_id" << std::endl;
            return 1;
        }

        // Debugging: Show the values of user_id and room_id
        std::cout << "User ID: " << argv[3] << " | Room ID: " << argv[4] << std::endl;

        // Validate user ID and room ID
        if (!isValidUserId(argv[3])) {
            std::cerr << "Invalid user ID format." << std::endl;
            return 1;
        }
        if (!isValidRoomId(argv[4])) {
            std::cerr << "Invalid room ID format." << std::endl;
            return 1;
        }

        // Call the logappend function
        logappend(argv[2], argv[3], argv[4]);

        // Generate a token using the user_id and room_id
        std::string token = generateToken(std::string(argv[3]) + std::string(argv[4]));  // Concatenate user_id and room_id
        std::cout << "Generated Token: " << token << std::endl;
    } 
    else if (command == "logread") {
        if (argc < 3) {
            std::cerr << "Usage: secure_logging.exe logread user_id" << std::endl;
            return 1;
        }
        logread(argv[2]);
    } 
    else {
        std::cerr << "Unknown command: " << command << std::endl;
        return 1;
    }

    return 0;
}
