/**
 * @file SmartBuffer.inl
 * @brief Implementation of the SmartBuffer template methods.
 */

#include <algorithm>
#include <cstring>
#include <stdexcept>
#include <type_traits>

/**
 * @brief Constructs a SmartBuffer with an optional initial capacity.
 * @param initialCapacity The initial capacity to reserve in the buffer.
 */
inline SmartBuffer::SmartBuffer(size_t initialCapacity)
    : buffer(initialCapacity, 0), readOffset(0), writeOffset(0) {}

/**
 * @brief Ensures the buffer has enough capacity for additional data.
 * @param additionalSize The required additional size.
 */
inline void SmartBuffer::ensureCapacity(size_t additionalSize) {
    size_t requiredSize = writeOffset + additionalSize;
    if (buffer.capacity() < requiredSize) {
        buffer.reserve(std::max(buffer.capacity() * 2, requiredSize));
    }
    if (buffer.size() < requiredSize) {
        buffer.resize(requiredSize);
    }
}

/**
 * @brief Injects raw data directly into the buffer.
 * @param rawData Pointer to the raw data to inject.
 * @param size The size of the raw data in bytes.
 */
inline void SmartBuffer::inject(const uint8_t* rawData, size_t size) {
    ensureCapacity(size);
    std::memcpy(buffer.data() + writeOffset, rawData, size);
    writeOffset += size;
}

/**
 * @brief Writes a value of type T into the buffer.
 * @tparam T The type of the value to write.
 * @param value The value to write.
 */
template <typename T> inline void SmartBuffer::write(const T& value) {
    if constexpr (std::is_trivially_copyable_v<T>) {
        ensureCapacity(sizeof(T));
        std::memcpy(buffer.data() + writeOffset, &value, sizeof(T));
        writeOffset += sizeof(T);
    } else if constexpr (std::is_same_v<T, std::string>) {
        uint32_t length = static_cast<uint32_t>(value.size());
        write(length);
        ensureCapacity(length);
        std::memcpy(buffer.data() + writeOffset, value.data(), length);
        writeOffset += length;
    } else {
        static_assert(false, "Unsupported non-trivial type");
    }
}

/**
 * @brief Reads a value of type T from the buffer.
 * @tparam T The type of the value to read.
 * @return The value read from the buffer.
 */
template <typename T> inline T SmartBuffer::read() {
    if constexpr (std::is_trivially_copyable_v<T>) {
        if (readOffset + sizeof(T) > writeOffset) {
            throw std::runtime_error("Buffer underflow");
        }
        T value;
        std::memcpy(&value, buffer.data() + readOffset, sizeof(T));
        readOffset += sizeof(T);
        return value;
    } else if constexpr (std::is_same_v<T, std::string>) {
        uint32_t length = read<uint32_t>();
        if (readOffset + length > writeOffset) {
            throw std::runtime_error("Buffer underflow");
        }
        std::string value(buffer.begin() + readOffset,
                          buffer.begin() + readOffset + length);
        readOffset += length;
        return value;
    } else {
        static_assert(false, "Unsupported non-trivial type");
    }
}

/**
 * @brief Overloads the << operator to write data into the buffer.
 * @tparam T The type of data to write.
 * @param value The data to write.
 * @return Reference to the current instance of SmartBuffer.
 */
template <typename T>
inline SmartBuffer& SmartBuffer::operator<<(const T& value) {
    write(value);
    return *this;
}

/**
 * @brief Overloads the >> operator to read data from the buffer.
 * @tparam T The type of data to read.
 * @param value Reference to store the read data.
 * @return Reference to the current instance of SmartBuffer.
 */
template <typename T> inline SmartBuffer& SmartBuffer::operator>>(T& value) {
    value = read<T>();
    return *this;
}

/**
 * @brief Resets the buffer by clearing all data.
 */
inline void SmartBuffer::reset() {
    buffer.clear();
    buffer.shrink_to_fit();
    readOffset = 0;
    writeOffset = 0;
}

/**
 * @brief Resets the read offset to the beginning of the buffer.
 */
inline void SmartBuffer::resetRead() {
    readOffset = 0;
}

/**
 * @brief Gets the size of the written data in the buffer.
 * @return The size in bytes of the data.
 */
inline size_t SmartBuffer::getSize() const {
    return writeOffset;
}

/**
 * @brief Gets a pointer to the buffer's data.
 * @return Constant pointer to the buffer's data.
 */
inline const uint8_t* SmartBuffer::getBuffer() const {
    return buffer.data();
}
