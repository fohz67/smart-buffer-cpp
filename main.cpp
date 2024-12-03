#include "SmartBuffer.hpp"
#include <iostream>

int main() {
    SmartBuffer buffer;

    // Writing data to the buffer
    buffer.writeInt8(42);
    buffer.writeInt16(2024);
    buffer.writeInt32(123456789);
    buffer.writeFloat(3.14159f);
    buffer.writeString("Brain rot");

    std::cout << "Buffer written successfully" << std::endl;

    // Reset read offset
    buffer.resetRead();

    // Reading data back from the buffer
    std::cout << "Read Int8: " << (int) buffer.readInt8() << std::endl;
    std::cout << "Read Int16: " << buffer.readInt16() << std::endl;
    std::cout << "Read Int32: " << buffer.readInt32() << std::endl;
    std::cout << "Read Float: " << buffer.readFloat() << std::endl;
    std::cout << "Read String: " << buffer.readString() << std::endl;

    return 0;
}
