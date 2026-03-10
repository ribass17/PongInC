build:
	gcc -std=c99 -Wall ./src/*.c -lSDL2 -o game

run:
	./game

test:
	gcc -std=c99 -Wall -DUNIT_TEST ./src/main.c ./tests/test_game.c ./tests/test_sdl_stubs.c -o tests/game_tests
	./tests/game_tests

clean:
	rm -f game tests/game_tests
