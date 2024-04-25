# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -Wextra -pedantic -std=c++17

# Source files
SRCS = componente_gigante_unordered_set.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = myprogram.exe

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Rule to build object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	del $(OBJS) $(TARGET)