# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -Iinclude

# Source files
SRC := src/main.cpp src/SmartBuffer.cpp

# Target executable
TARGET := smartbuffer

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Clean up build files
clean:
	rm -f $(TARGET)

.PHONY: all clean