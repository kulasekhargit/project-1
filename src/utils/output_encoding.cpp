#include "../../include/output_encoding.h"

// Function to encode special characters to prevent injection attacks or XSS
std::string encodeOutput(const std::string& input) {
    std::string encoded;
    for (char c : input) {
        switch (c) {
            case '<': encoded += "&lt;"; break;
            case '>': encoded += "&gt;"; break;
            case '&': encoded += "&amp;"; break;
            case '\'': encoded += "&apos;"; break;
            case '"': encoded += "&quot;"; break;
            default: encoded += c;
        }
    }
    return encoded;
}

// Function to decode encoded characters back to original format
std::string decodeOutput(const std::string& encoded) {
    std::string decoded = encoded;
    size_t pos = 0;

    // Replace encoded characters with their original counterparts
    while ((pos = decoded.find("&lt;")) != std::string::npos) decoded.replace(pos, 4, "<");
    while ((pos = decoded.find("&gt;")) != std::string::npos) decoded.replace(pos, 4, ">");
    while ((pos = decoded.find("&amp;")) != std::string::npos) decoded.replace(pos, 5, "&");
    while ((pos = decoded.find("&apos;")) != std::string::npos) decoded.replace(pos, 6, "'");
    while ((pos = decoded.find("&quot;")) != std::string::npos) decoded.replace(pos, 6, "\"");

    return decoded;
}
