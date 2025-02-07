#include <algorithm>
#include <cstring>
#include <stdexcept>
#include <type_traits>

using namespace std;

inline SmartBuffer::SmartBuffer(size_t initialCapacity)
    : buffer(initialCapacity, 0), readOffset(0), writeOffset(0)
{
}

inline void SmartBuffer::ensureCapacity(size_t additionalSize)
{
    size_t requiredSize = writeOffset + additionalSize;
    if (buffer.capacity() < requiredSize)
    {
        buffer.reserve(max(buffer.capacity() * 2, requiredSize));
    }
    if (buffer.size() < requiredSize)
    {
        buffer.resize(requiredSize);
    }
}

inline void SmartBuffer::inject(const uint8_t* rawData, size_t size)
{
    ensureCapacity(size);
    memcpy(buffer.data() + writeOffset, rawData, size);
    writeOffset += size;
}

template <typename T>
inline void SmartBuffer::write(const T& value)
{
    if constexpr (is_trivially_copyable_v<T>)
    {
        ensureCapacity(sizeof(T));
        memcpy(buffer.data() + writeOffset, &value, sizeof(T));
        writeOffset += sizeof(T);
    }
    else if constexpr (is_same_v<T, string>)
    {
        uint32_t length = static_cast<uint32_t>(value.size());
        write(length);
        ensureCapacity(length);
        memcpy(buffer.data() + writeOffset, value.data(), length);
        writeOffset += length;
    }
}

template <typename T>
inline T SmartBuffer::read()
{
    if constexpr (is_trivially_copyable_v<T>)
    {
        if (readOffset + sizeof(T) > writeOffset)
        {
            throw runtime_error("Buffer underflow");
        }
        T value;
        memcpy(&value, buffer.data() + readOffset, sizeof(T));
        readOffset += sizeof(T);
        return value;
    }
    else if constexpr (is_same_v<T, string>)
    {
        uint32_t length = read<uint32_t>();
        if (readOffset + length > writeOffset)
        {
            throw runtime_error("Buffer underflow");
        }
        string value(buffer.begin() + readOffset, buffer.begin() + readOffset + length);
        readOffset += length;
        return value;
    }
}

template <typename T>
inline SmartBuffer& SmartBuffer::operator<<(const T& value)
{
    write(value);
    return *this;
}

template <typename T>
inline SmartBuffer& SmartBuffer::operator>>(T& value)
{
    value = read<T>();
    return *this;
}

inline void SmartBuffer::reset()
{
    buffer.clear();
    buffer.shrink_to_fit();
    readOffset = 0;
    writeOffset = 0;
}

inline void SmartBuffer::resetRead()
{
    readOffset = 0;
}

inline size_t SmartBuffer::getSize() const
{
    return writeOffset;
}

inline const uint8_t* SmartBuffer::getBuffer() const
{
    return buffer.data();
}
