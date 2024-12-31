CC=gcc
CFLAGS=-Wall -Wextra -Werror -Wpedantic -std=c2x
BIN_DIR = bin
BUILD_DIR = build
TARGET = $(BIN_DIR)/server
OBJS = $(BUILD_DIR)/server.o $(BUILD_DIR)/main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(BUILD_DIR)/server.o: server.c server.h
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c server.c -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/main.o: main.c server.h
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c main.c -o $(BUILD_DIR)/main.o

clean:
	rm -rf $(BIN_DIR) $(BUILD_DIR)

.PHONY: all clean
