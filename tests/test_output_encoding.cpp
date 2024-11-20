#include "../include/output_encoding.h"
#include <cassert>
#include <iostream>

void testOutputEncoding() {
    // Test encoding
    std::string original = "<Test>&String'";
    std::string encoded = encodeOutput(original);
    assert(encoded == "&lt;Test&gt;&amp;String&apos;");
    std::cout << "Encoding test passed!" << std::endl;

    // Test decoding (if decodeOutput is implemented)
    // std::string decoded = decodeOutput(encoded);
    // assert(decoded == original);
    // std::cout << "Decoding test passed!" << std::endl;
}

int main() {
    testOutputEncoding();
    return 0;
}
