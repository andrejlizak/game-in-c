# Makefile for Snake Game

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -std=c11

# Libraries
LIBS = -lcurses -lm

# Source files
SRCS = program.c

# Output executable
OUT = snake_game

# Build rule
all: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(OUT) $(LIBS)

# Clean rule
clean:
	rm -f $(OUT)
