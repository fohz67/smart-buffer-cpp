#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

class SmartBuffer
{
   public:
    explicit SmartBuffer(size_t initialCapacity = 8);

    void inject(const uint8_t* rawData, size_t size);

    template <typename T>
    void write(const T& value);

    template <typename T>
    T read();

    template <typename T>
    SmartBuffer& operator<<(const T& value);

    template <typename T>
    SmartBuffer& operator>>(T& value);

    void reset();
    void resetRead();

    [[nodiscard]] size_t getSize() const;
    [[nodiscard]] const uint8_t* getBuffer() const;

   private:
    void ensureCapacity(size_t additionalSize);

    std::vector<uint8_t> buffer;

    size_t readOffset = 0;
    size_t writeOffset = 0;
};

#include "SmartBuffer.inl"
