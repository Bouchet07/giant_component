# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -Wextra -pedantic -std=c++17 -Ofast

# Source files
SRCS = main.cpp

# Executable name
TARGET = main.exe

# Default target
all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

# Clean rule
clean:
	del $(TARGET)