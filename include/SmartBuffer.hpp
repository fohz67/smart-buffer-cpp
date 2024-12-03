#ifndef SMARTBUFFER_HPP
#define SMARTBUFFER_HPP

#include <vector>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <cstring>

/**
 * @class SmartBuffer
 * @brief A dynamic buffer class for efficient reading and writing of binary data.
 */
class SmartBuffer {
public:
    /**
     * @brief Constructs a SmartBuffer with an initial capacity.
     * @param initialCapacity Initial capacity of the buffer in bytes.
     */
    explicit SmartBuffer(size_t initialCapacity = 256);

    /**
     * @brief Writes a single byte to the buffer.
     * @param value The byte value to write.
     */
    void writeInt8(int8_t value);

    /**
     * @brief Writes a 16-bit integer to the buffer.
     * @param value The 16-bit integer to write.
     */
    void writeInt16(int16_t value);

    /**
     * @brief Writes a 32-bit integer to the buffer.
     * @param value The 32-bit integer to write.
     */
    void writeInt32(int32_t value);

    /**
     * @brief Writes a floating-point number to the buffer.
     * @param value The float value to write.
     */
    void writeFloat(float value);

    /**
     * @brief Writes a string to the buffer.
     * @param value The string to write.
     */
    void writeString(const std::string& value);

    /**
     * @brief Writes raw bytes to the buffer.
     * @param data Pointer to the data to write.
     * @param size Number of bytes to write.
     */
    void writeBytes(const uint8_t* data, size_t size);

    /**
     * @brief Reads a single byte from the buffer.
     * @return The read byte.
     */
    int8_t readInt8();

    /**
     * @brief Reads a 16-bit integer from the buffer.
     * @return The read 16-bit integer.
     */
    int16_t readInt16();

    /**
     * @brief Reads a 32-bit integer from the buffer.
     * @return The read 32-bit integer.
     */
    int32_t readInt32();

    /**
     * @brief Reads a floating-point number from the buffer.
     * @return The read float value.
     */
    float readFloat();

    /**
     * @brief Reads a string from the buffer.
     * @return The read string.
     */
    std::string readString();

    /**
     * @brief Reads raw bytes from the buffer into a destination array.
     * @param dest Pointer to the destination buffer.
     * @param size Number of bytes to read.
     */
    void readBytes(uint8_t* dest, size_t size);

    /**
     * @brief Resets the buffer for both reading and writing.
     */
    void reset();

    /**
     * @brief Resets the read offset of the buffer.
     */
    void resetRead();

    /**
     * @brief Returns the current size of the written data in the buffer.
     * @return Size of the written data in bytes.
     */
    size_t getSize() const;

    /**
     * @brief Returns a pointer to the raw buffer data.
     * @return Pointer to the buffer data.
     */
    const uint8_t* getBuffer() const;

private:
    std::vector<uint8_t> buffer;     ///< The dynamic buffer storage.
    size_t readOffset;               ///< The current read position in the buffer.
    size_t writeOffset;              ///< The current write position in the buffer.

    /**
     * @brief Ensures the buffer has enough capacity for additional writes.
     * @param additionalSize The number of additional bytes required.
     */
    void ensureCapacity(size_t additionalSize);
};

#endif // SMARTBUFFER_HPP
