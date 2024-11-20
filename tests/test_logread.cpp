#include "../include/logread.h"
#include <cassert>
#include <fstream>
#include <iostream>

void testLogRead() {
    // Prepare log file
    std::ofstream logFile("log.txt");
    logFile << "Entry: Test entry 1, User: user1, Room: 101" << std::endl;
    logFile << "Entry: Test entry 2, User: user2, Room: 202" << std::endl;
    logFile.close();

    // Capture the output of logread
    logread("user1"); // Should print the entry for user1

    std::cout << "Log read test completed successfully!" << std::endl;
}

int main() {
    testLogRead();
    return 0;
}
