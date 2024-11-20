#include "../include/logappend.h"
#include <cassert>
#include <fstream>
#include <iostream>

void testLogAppend() {
    // Clean up previous log file
    std::ofstream ofs("log.txt", std::ofstream::trunc);
    ofs.close();

    // Append logs
    logappend("Test entry 1", "user1", "101");
    logappend("Test entry 2", "user2", "202");

    // Verify log file contents
    std::ifstream logFile("log.txt");
    std::string line;

    assert(logFile.is_open());
    std::getline(logFile, line);
    assert(line == "Entry: Test entry 1, User: user1, Room: 101");
    std::getline(logFile, line);
    assert(line == "Entry: Test entry 2, User: user2, Room: 202");

    logFile.close();

    std::cout << "All log append tests passed!" << std::endl;
}

int main() {
    testLogAppend();
    return 0;
}
