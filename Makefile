# Compiler options
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic
LDFLAGS = -lSDL2 -lSDL2_ttf

# Directories
SRC_DIR = src
BUILD_DIR = build

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Targets
TARGET = $(BUILD_DIR)/termu

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean

