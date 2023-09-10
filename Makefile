build:
	gcc  -std=c99  -Wall -lSDL2 -o Teste ./src/*.c -o game

run:
	./game

clean:
	rm game
