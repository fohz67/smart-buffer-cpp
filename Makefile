CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

SRC = SmartBuffer.cpp main.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = smartbuffer

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
