# Makefile for Unix-like systems (Linux, macOS, WSL).
#   make        build ./studentsort
#   make run    build and start the program
#   make clean  remove the executable and object files
CXX      := g++
CXXFLAGS := -O2 -std=c++17 -Wall -Wextra -Iinclude
TARGET   := studentsort
SRC      := $(wildcard src/*.cpp)
OBJ      := $(SRC:src/%.cpp=build/%.o)
HDR      := $(wildcard include/*.h)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

build/%.o: src/%.cpp $(HDR) | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build:
	mkdir -p build

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf build $(TARGET)

.PHONY: all run clean
