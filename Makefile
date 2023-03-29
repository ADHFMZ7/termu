# Compiler options
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic
LDFLAGS = -lSDL2

# Directories
SRC_DIR = src
BUILD_DIR = build

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Targets
TARGET = $(BUILD_DIR)/program

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

