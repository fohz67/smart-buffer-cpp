CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -Iinclude

SRC := src/main.cpp src/SmartBuffer.cpp
TARGET := smartbuffer

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)

.PHONY: all clean
