# Makefile

CXX       := g++
CXXFLAGS  := -std=c++17 -Wall -Wextra -Iinclude
SRC       := $(wildcard src/*.cpp)
OBJ       := $(patsubst src/%.cpp, build/%.o, $(SRC))
TARGET    := recipe_app

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Order-only prerequisite: ensure build/ exists before compiling .o files
build/%.o: src/%.cpp | build_dir
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build/ in a cross-platform fashion
.PHONY: build_dir
build_dir:
ifeq ($(OS),Windows_NT)
	if not exist build mkdir build
else
	mkdir -p build
endif

# Clean up
clean:
ifeq ($(OS),Windows_NT)
	rmdir /S /Q build
	del $(TARGET).exe
else
	rm -rf build $(TARGET)
endif

.PHONY: all clean build_dir
