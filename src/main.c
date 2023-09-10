#include <stdio.h>
#include <SDL2/SDL.h>
#include "./constants.h"

int gameIsRunning = FALSE; 
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int lastFrameTime = 0;

struct ball
{
    float x, y, width, height ;
}ball;


int initializeWindow(void){
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		fprintf(stderr, "Erro ao iniciar SDL2.\n");
		return FALSE;
	}	
	window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
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

void processInput(){
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        gameIsRunning = FALSE;
        break;
    case SDL_KEYDOWN:
        if(event.key.keysym.sym == SDLK_ESCAPE)
            gameIsRunning = FALSE; 
        break;
    }
}
void setup(){
    ball.x = 1;
    ball.y = 1;
    ball.height = 15;
    ball.width = 15;
}

void update(){
    int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - lastFrameTime); 
    
    if(timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME){
        SDL_Delay(timeToWait);
    }
    
    float   deltaTime = ((SDL_GetTicks() - lastFrameTime) /  1000.0f);
    

    lastFrameTime = SDL_GetTicks();
    
}


void render(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect ballRect ={ 
        ball.x,
        ball.y, 
        ball.width,
        ball.height
    };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &ballRect);
    SDL_RenderPresent(renderer);
}
void stopGame(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


int  main(){
	gameIsRunning = initializeWindow();

    setup();

    while(gameIsRunning){
        processInput();
        update();
        render();
    }

    stopGame();

	return 0;
}