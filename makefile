# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -pedantic

# Directories
SRC_DIRS := . QBits QGates
BUILD_DIR := build
INCLUDES := -IQBits -IQGates

# Source and object files
SRCS := main.cpp $(wildcard QBits/*.cpp) $(wildcard QGates/*.cpp)
OBJS := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Target binary
TARGET := $(BUILD_DIR)/quantum_sim.exe

# Default rule
all: $(TARGET)

# Link the final executable
$(TARGET): $(OBJS)
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

# Rule to compile source files into object files
$(BUILD_DIR)/%.o: %.cpp
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean rule
.PHONY: clean
clean:
	@if exist "$(BUILD_DIR)" rmdir /S /Q "$(BUILD_DIR)"
