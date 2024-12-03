/*
** FILENAME: SmartBuffer.cpp
** PROJECT: SmartBuffer Implementation
** AUTHOR: fōhz
** DESCRIPTION: Implementation of the SmartBuffer class for managing dynamic binary data buffers.
*/

#include "SmartBuffer.hpp"

SmartBuffer::SmartBuffer(size_t initialCapacity)
        : buffer(initialCapacity, 0), readOffset(0), writeOffset(0) {}

/**
 * @brief Ensures the buffer has enough capacity to accommodate additional data.
 * @param additionalSize Number of bytes to ensure the buffer can hold.
 */
void SmartBuffer::ensureCapacity(size_t additionalSize) {
    if (writeOffset + additionalSize > buffer.size()) {
        buffer.resize(buffer.size() + additionalSize * 2);
    }
}

/**
 * @brief Writes a single byte (int8_t) to the buffer.
 * @param value The byte value to write.
 */
void SmartBuffer::writeInt8(int8_t value) {
    ensureCapacity(sizeof(int8_t));
    buffer[writeOffset++] = value;
}

/**
 * @brief Writes a 16-bit integer to the buffer.
 * @param value The 16-bit integer to write.
 */
void SmartBuffer::writeInt16(int16_t value) {
    ensureCapacity(sizeof(int16_t));
    std::memcpy(&buffer[writeOffset], &value, sizeof(int16_t));
    writeOffset += sizeof(int16_t);
}

/**
 * @brief Writes a 32-bit integer to the buffer.
 * @param value The 32-bit integer to write.
 */
void SmartBuffer::writeInt32(int32_t value) {
    ensureCapacity(sizeof(int32_t));
    std::memcpy(&buffer[writeOffset], &value, sizeof(int32_t));
    writeOffset += sizeof(int32_t);
}

/**
 * @brief Writes a floating-point number to the buffer.
 * @param value The float value to write.
 */
void SmartBuffer::writeFloat(float value) {
    ensureCapacity(sizeof(float));
    std::memcpy(&buffer[writeOffset], &value, sizeof(float));
    writeOffset += sizeof(float);
}

/**
 * @brief Writes a string to the buffer.
 * @param value The string to write.
 */
void SmartBuffer::writeString(const std::string &value) {
    writeInt16(static_cast<int16_t>(value.size()));
    ensureCapacity(value.size());
    std::memcpy(&buffer[writeOffset], value.data(), value.size());
    writeOffset += value.size();
}

/**
 * @brief Writes raw bytes to the buffer.
 * @param data Pointer to the data to write.
 * @param size Number of bytes to write.
 */
void SmartBuffer::writeBytes(const uint8_t *data, size_t size) {
    ensureCapacity(size);
    std::memcpy(&buffer[writeOffset], data, size);
    writeOffset += size;
}

/**
 * @brief Reads a single byte (int8_t) from the buffer.
 * @return The read byte.
 */
int8_t SmartBuffer::readInt8() {
    if (readOffset + sizeof(int8_t) > writeOffset) {
        throw std::runtime_error("Buffer underflow");
    }
    return buffer[readOffset++];
}

/**
 * @brief Reads a 16-bit integer from the buffer.
 * @return The read 16-bit integer.
 */
int16_t SmartBuffer::readInt16() {
    if (readOffset + sizeof(int16_t) > writeOffset) {
        throw std::runtime_error("Buffer underflow");
    }
    int16_t value;
    std::memcpy(&value, &buffer[readOffset], sizeof(int16_t));
    readOffset += sizeof(int16_t);
    return value;
}

/**
 * @brief Reads a 32-bit integer from the buffer.
 * @return The read 32-bit integer.
 */
int32_t SmartBuffer::readInt32() {
    if (readOffset + sizeof(int32_t) > writeOffset) {
        throw std::runtime_error("Buffer underflow");
    }
    int32_t value;
    std::memcpy(&value, &buffer[readOffset], sizeof(int32_t));
    readOffset += sizeof(int32_t);
    return value;
}

/**
 * @brief Reads a floating-point number from the buffer.
 * @return The read float value.
 */
float SmartBuffer::readFloat() {
    if (readOffset + sizeof(float) > writeOffset) {
        throw std::runtime_error("Buffer underflow");
    }
    float value;
    std::memcpy(&value, &buffer[readOffset], sizeof(float));
    readOffset += sizeof(float);
    return value;
}

/**
 * @brief Reads a string from the buffer.
 * @return The read string.
 */
std::string SmartBuffer::readString() {
    int16_t length = readInt16();
    if (readOffset + length > writeOffset) {
        throw std::runtime_error("Buffer underflow");
    }
    std::string value(reinterpret_cast<char *>(&buffer[readOffset]), length);
    readOffset += length;
    return value;
}

/**
 * @brief Reads raw bytes from the buffer into a destination array.
 * @param dest Pointer to the destination buffer.
 * @param size Number of bytes to read.
 */
void SmartBuffer::readBytes(uint8_t *dest, size_t size) {
    if (readOffset + size > writeOffset) {
        throw std::runtime_error("Buffer underflow");
    }
    std::memcpy(dest, &buffer[readOffset], size);
    readOffset += size;
}

/**
 * @brief Resets the buffer for both reading and writing.
 */
void SmartBuffer::reset() {
    readOffset = 0;
    writeOffset = 0;
}

/**
 * @brief Resets the read offset of the buffer.
 */
void SmartBuffer::resetRead() {
    readOffset = 0;
}

/**
 * @brief Returns the current size of the written data in the buffer.
 * @return Size of the written data in bytes.
 */
size_t SmartBuffer::getSize() const {
    return writeOffset;
}

/**
 * @brief Returns a pointer to the raw buffer data.
 * @return Pointer to the buffer data.
 */
const uint8_t *SmartBuffer::getBuffer() const {
    return buffer.data();
}
