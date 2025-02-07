#include <cstdint>
#include <iostream>
#include "SmartBuffer.hpp"

int main() {
    SmartBuffer buffer;

    buffer << uint8_t(255) << uint16_t(65535) << uint32_t(4294967295) << int32_t(-42)
           << double(3.14159) << std::string("Hello");

    std::cout << "Buffer size after writing: " << buffer.getSize() << " bytes\n\n";

    buffer.resetRead();

    uint8_t     byte_val;
    uint16_t    short_val;
    uint32_t    uint_val;
    int32_t     int_val;
    double      double_val;
    std::string str_val;

    buffer >> byte_val >> short_val >> uint_val >> int_val >> double_val >> str_val;

    std::cout << "Read values:\n";
    std::cout << "Byte value: " << static_cast<int>(byte_val) << "\n";
    std::cout << "Short value: " << short_val << "\n";
    std::cout << "Unsigned int value: " << uint_val << "\n";
    std::cout << "Signed int value: " << int_val << "\n";
    std::cout << "Double value: " << double_val << "\n";
    std::cout << "String value: " << str_val << "\n";

    return 0;
}
