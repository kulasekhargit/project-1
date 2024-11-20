#include "../include/input_validation.h"
#include <cassert>
#include <iostream>

void testInputValidation() {
    // Test valid user IDs
    assert(isValidUserId("user123"));
    assert(isValidUserId("testUser"));

    // Test invalid user IDs
    assert(!isValidUserId("user"));
    assert(!isValidUserId("user_with_symbols!"));

    // Test valid room IDs
    assert(isValidRoomId("123"));
    assert(isValidRoomId("room123"));
    assert(isValidRoomId("A123"));

    // Test invalid room IDs
    assert(!isValidRoomId("0123")); // Leading zero
    assert(!isValidRoomId("room")); // No numbers

    std::cout << "All input validation tests passed!" << std::endl;
}

int main() {
    testInputValidation();
    return 0;
}
