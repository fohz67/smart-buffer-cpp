/**
 * @file SmartBuffer.inl
 * @brief Implementation of the SmartBuffer template methods.
 */

#include <algorithm>
#include <cstring>
#include <stdexcept>

/**
 * @brief Constructs a SmartBuffer with an optional initial capacity.
 * @param initialCapacity The initial capacity to reserve in the buffer.
 */
inline SmartBuffer::SmartBuffer(size_t initialCapacity) : buffer(), readOffset(0), writeOffset(0)
{
    buffer.reserve(initialCapacity);
}

/**
 * @brief Ensures the buffer has enough capacity for additional data.
 * @param additionalSize The required additional size.
 */
inline void SmartBuffer::ensureCapacity(size_t additionalSize)
{
    if (buffer.size() < writeOffset + additionalSize)
    {
        buffer.resize(writeOffset + additionalSize);
    }
}

/**
 * @brief Injects raw data directly into the buffer.
 * @param rawData Pointer to the raw data to inject.
 * @param size The size of the raw data in bytes.
 */
inline void SmartBuffer::inject(const uint8_t *rawData, size_t size)
{
    ensureCapacity(size);
    std::memcpy(buffer.data() + writeOffset, rawData, size);
    writeOffset += size;
}

/**
 * @brief Overloads the << operator to write data into the buffer.
 * @tparam T The type of data to write.
 * @param value The data to write.
 * @return Reference to the current instance of SmartBuffer.
 */
template <typename T> inline SmartBuffer &SmartBuffer::operator<<(const T &value)
{
    write(value);
    return *this;
}

/**
 * @brief Overloads the >> operator to read data from the buffer.
 * @tparam T The type of data to read.
 * @param value Reference to store the read data.
 * @return Reference to the current instance of SmartBuffer.
 */
template <typename T> inline SmartBuffer &SmartBuffer::operator>>(T &value)
{
    value = read<T>();
    return *this;
}

/**
 * @brief Resets the buffer by clearing all data.
 */
inline void SmartBuffer::reset()
{
    buffer.clear();
    readOffset = 0;
    writeOffset = 0;
}

/**
 * @brief Resets the read offset to the beginning of the buffer.
 */
inline void SmartBuffer::resetRead()
{
    readOffset = 0;
}

/**
 * @brief Gets the size of the written data in the buffer.
 * @return The size in bytes of the data.
 */
inline size_t SmartBuffer::getSize() const
{
    return writeOffset;
}

/**
 * @brief Gets a pointer to the buffer's data.
 * @return Constant pointer to the buffer's data.
 */
inline const uint8_t *SmartBuffer::getBuffer() const
{
    return buffer.data();
}
