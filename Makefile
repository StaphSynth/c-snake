# Makefile for C Snake Game

# Compiler and flags
CC = gcc
CFLAGS = $(shell sdl2-config --cflags) -Wall -Wextra -std=c99
LIBS = $(shell sdl2-config --libs)

# Directories
BIN_DIR = bin

# Target executable
TARGET = $(BIN_DIR)/snake

# Source files
SOURCES = main.c

# Object files (automatically generated from sources, placed in bin directory)
OBJECTS = $(SOURCES:%.c=$(BIN_DIR)/%.o)

# Default target
all: $(TARGET)

# Create bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Build the executable
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(OBJECTS) $(LIBS) -o $(TARGET)

# Build object files
$(BIN_DIR)/%.o: %.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -rf $(BIN_DIR)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Rebuild everything from scratch
rebuild: clean all

# Mark these targets as not being files
.PHONY: all clean run rebuild