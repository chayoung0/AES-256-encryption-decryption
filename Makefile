# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Name of the executable
TARGET = zer0day

# Source files (add all your .c files here)
SRCS = main.c aes_core.c aes_key.c file_handling.c ui.c

# Object files (automatically generated from source files)
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	del /Q *.o


# Phony targets
.PHONY: all clean