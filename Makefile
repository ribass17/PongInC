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

test:
	$(CC) -std=c99 -Wall -Wextra -Werror -DUNIT_TEST ./src/main.c ./tests/test_game.c ./tests/test_sdl_stubs.c -o tests/game_tests
	./tests/game_tests

clean:
	rm -f $(TARGET) tests/game_tests
