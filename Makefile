CC=gcc
CFLAGS=-Wall -Wextra -Werror -Wpedantic -std=c2x
TARGET = ./bin/server
BUILD_DIR = build
OBJS = $(BUILD_DIR)/server.o $(BUILD_DIR)/main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(BUILD_DIR)/server.o: server.c server.h
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c server.c -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/main.o: main.c server.h
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c main.c -o $(BUILD_DIR)/main.o

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
