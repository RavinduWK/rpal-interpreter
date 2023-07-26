# all:	
# 	g++ -std=c++11 token.cpp TreeStandardizer.cpp lexer.cpp Control.cpp parser.cpp Environment.cpp CSEMachine.cpp p1.cpp -o rpal20 
# cl: 
# 	rm -f p1;

# Compiler and compiler flags
CXX := g++
CXXFLAGS := -std=c++11

# Directories
SRC_DIR := rpal
BUILD_DIR := build
BIN_DIR := bin

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Output binary
TARGET := rpal20

# Default target, build the program
all: create_build_dir $(TARGET)

# Rule to build the program
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to compile the source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to create the build directory
create_build_dir:
	mkdir -p $(BUILD_DIR)

# Clean up the generated files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# PHONY target to avoid conflicts with files named "all" or "clean"
.PHONY: all create_build_dir clean
