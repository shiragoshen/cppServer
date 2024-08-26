# Compiler settings
CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -pthread
LDFLAGS =

# Directories (no escaping needed here, just for clear visibility)
SRC_DIR = "/Users/shiragoshen/BIU/adv programming/cppServer"
OBJ_DIR = "/Users/shiragoshen/BIU/adv programming/cppServer/obj"
BIN_DIR = "/Users/shiragoshen/BIU/adv programming/cppServer/bin"

# Executable
EXECUTABLE = $(BIN_DIR)/server

# Source files
SOURCES = handle_client.cpp main.cpp recommendations.cpp record_history.cpp server.cpp

# Object files
OBJECTS = $(addprefix $(OBJ_DIR)/, $(SOURCES:.cpp=.o))

# Default target
all: $(EXECUTABLE)

# Linking
$(EXECUTABLE): $(OBJECTS)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

# Compiling each source explicitly
$(OBJ_DIR)/handle_client.o: $(SRC_DIR)/handle_client.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/handle_client.cpp -o $(OBJ_DIR)/handle_client.o

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/recommendations.o: $(SRC_DIR)/recommendations.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/recommendations.cpp -o $(OBJ_DIR)/recommendations.o

$(OBJ_DIR)/record_history.o: $(SRC_DIR)/record_history.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/record_history.cpp -o $(OBJ_DIR)/record_history.o

$(OBJ_DIR)/server.o: $(SRC_DIR)/server.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/server.cpp -o $(OBJ_DIR)/server.o

# Cleaning up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all clean