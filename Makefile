# Compiler
CC = gcc

# Flags
CFLAGS = -Wall -Wextra -Werror -std=c11 -g
LDFLAGS =

# Directories
SRC_DIR = src
OBJ_DIR = obj
SAVE_DIR = saves

# Target
TARGET = chess

# Source files
SRCS = \
	main.c \
	moves.c \
	board.c \
	game.c \
	input.c \
	history.c \
	file_io.c \
	display.c

# Full paths
SRC_FILES = $(addprefix $(SRC_DIR)/, $(SRCS))
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# Default rule
all: $(TARGET)
	@mkdir -p $(SAVE_DIR)
	@echo "Build complete! Run with: ./$(TARGET) or make run"

# Link
$(TARGET): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $@ $(LDFLAGS)

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Run
run: $(TARGET)
	@mkdir -p $(SAVE_DIR)
	./$(TARGET)

# Clean
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Clean everything including saves
cleanall: clean
	rm -rf $(SAVE_DIR)

# Rebuild
re: clean all

.PHONY: all run clean cleanall re