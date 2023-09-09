#include <stdio.h>
#include <SDL2/SDL.h>
#include "./constants.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int initialize_window(void){
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		fprintf(stderr, "Erro ao iniciar SDL2.\n");
		return FALSE;
	}	
	window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_WIDTH,
        SDL_WINDOW_BORDERLESS
    );
    if(!window){
        fprintf(stderr,"Erro ao criar janela no SDL.\n");
        return FALSE;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer){
        fprintf(stderr,"Erro ao criar renderizacao.\n");
        return FALSE;
    }

	return TRUE;
}


int  main()
{
	printf("Game is running...\n");
    initialize_window();
	return 0;
}