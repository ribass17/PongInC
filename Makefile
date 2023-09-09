build:
	gcc  -std=c99 -I"include" -L"lib" -Wall -lSDL2main -lSDL2 -lSDL2_image -o Teste ./src/*.c -o game

run:
	./game

clean:
	rm game
