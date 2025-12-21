CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# List all your source files
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/board.c \
       $(SRC_DIR)/moves.c \
       $(SRC_DIR)/display.c \
       $(SRC_DIR)/input.c \
       $(SRC_DIR)/file_io.c \
       $(SRC_DIR)/history.c \
       $(SRC_DIR)/game.c

# Convert source files to object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET = chess

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean