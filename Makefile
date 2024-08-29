# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11 -g

# Target executable
TARGET = server_app

# Source files
SRCS = main.cpp handle_client.cpp recommendations.cpp record_history.cpp server.cpp

# Build directory for object files
BUILD_DIR = build

# Object files (placed in the build directory)
OBJS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Default target
all: $(TARGET)

# Link the object files to create the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile each source file into an object file in the build directory
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure the build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean up build artifacts
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Phony targets
.PHONY: all clean
