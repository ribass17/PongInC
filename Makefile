CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror
LDFLAGS = -lSDL2
TARGET = game
SRC = ./src/*.c

.PHONY: build run clean test

build:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: build
	./$(TARGET)

test: build
	@test -x ./$(TARGET)
	@echo "Build test passed: binary ./$(TARGET) generated successfully"

clean:
	rm -f $(TARGET)
