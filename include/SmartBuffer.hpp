#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

/**
 * @file SmartBuffer.hpp
 * @brief Declaration of the SmartBuffer class.
 */

/**
 * @class SmartBuffer
 * @brief A class for managing a dynamic binary data buffer.
 *
 * The SmartBuffer class allows for easy serialization and deserialization of various data types
 * into a dynamic buffer. It supports reading and writing of trivially copyable types and provides
 * specializations for non-trivial types like std::string.
 */
class SmartBuffer
{
  public:
    /**
     * @brief Constructs a SmartBuffer with an optional initial capacity.
     * @param initialCapacity The initial capacity to reserve in the buffer.
     */
    SmartBuffer(size_t initialCapacity = 8);

    /**
     * @brief Injects raw data directly into the buffer.
     * @param rawData Pointer to the raw data to inject.
     * @param size The size of the raw data in bytes.
     */
    void inject(const uint8_t *rawData, size_t size);


    /**
     * @brief Writes a value of type T into the buffer.
     * @tparam T The type of the value to write.
     * @param value The value to write.
     *
     * Supports trivially copyable types. For non-trivial types like std::string, there are
     * specializations provided.
     */
    template <typename T> void write(const T &value);

    /**
     * @brief Reads a value of type T from the buffer.
     * @tparam T The type of the value to read.
     * @return The value read from the buffer.
     *
     * Supports trivially copyable types. For non-trivial types like std::string, there are
     * specializations provided.
     */
    template <typename T> T read();

    /**
     * @brief Overloads the << operator to write data into the buffer.
     * @tparam T The type of data to write.
     * @param value The data to write.
     * @return Reference to the current instance of SmartBuffer.
     */
    template <typename T> SmartBuffer &operator<<(const T &value);

    /**
     * @brief Overloads the >> operator to read data from the buffer.
     * @tparam T The type of data to read.
     * @param value Reference to store the read data.
     * @return Reference to the current instance of SmartBuffer.
     */
    template <typename T> SmartBuffer &operator>>(T &value);

    /**
     * @brief Resets the buffer by clearing all data.
     */
    void reset();

    /**
     * @brief Resets the read offset to the beginning of the buffer.
     */
    void resetRead();

    /**
     * @brief Gets the size of the written data in the buffer.
     * @return The size in bytes of the data.
     */
    size_t getSize() const;

    /**
     * @brief Gets a pointer to the buffer's data.
     * @return Constant pointer to the buffer's data.
     */
    const uint8_t *getBuffer() const;

  private:
    /**
     * @brief Ensures the buffer has enough capacity for additional data.
     * @param additionalSize The required additional size.
     */
    void ensureCapacity(size_t additionalSize);

    std::vector<uint8_t> buffer; /**< Underlying byte buffer. */
    size_t readOffset;           /**< Current read offset in the buffer. */
    size_t writeOffset;          /**< Current write offset in the buffer. */
};

#include "SmartBuffer.inl"
