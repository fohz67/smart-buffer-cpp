#include <iostream>
#include "SmartBuffer.hpp"

int main() {
    SmartBuffer buffer;

    // Writing data into the buffer
    buffer << int8_t(127) << int16_t(32000) << int32_t(2147483647);
    buffer << float(3.14f) << std::string("Fohz fOhZ FoHz");

    // Reset the read offset to read from the beginning
    buffer.resetRead();

    // Reading data from the buffer
    int8_t a;
    int16_t b;
    int32_t c;
    float d;
    std::string e;

    buffer >> a >> b >> c >> d >> e;

    // Displaying the read values
    std::cout << "a = " << static_cast<int>(a) << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "e = " << e << std::endl;

    return 0;
}
