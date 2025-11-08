# Makefile for C Snake Game

# Compiler and flags
CC = gcc
CFLAGS = $(shell sdl2-config --cflags) -Wall -Wextra -std=c99
LIBS = $(shell sdl2-config --libs)

# Target executable
TARGET = snake

# Source files
SOURCES = main.c

# Object files (automatically generated from sources)
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $(TARGET)

# Build object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Rebuild everything from scratch
rebuild: clean all

# Mark these targets as not being files
.PHONY: all clean run rebuild