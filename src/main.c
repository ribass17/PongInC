#include <stdio.h>
#include <SDL2/SDL.h>
#include "./constants.h"

int gameIsRunning = FALSE; 
int colX = 1;
int colY = 1;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int lastFrameTime = 0;

struct ball
{
    float x, y, width, height;
}ball;

typedef struct
{
    float x, y, width, height;
}barra;

barra b1, b2; 



int initializeWindow(void){
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		fprintf(stderr, "Erro ao iniciar SDL2.\n");
		return FALSE;
	}	
	window = SDL_CreateWindow(
        "Pong in C",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0
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
    ball.x = (WINDOW_WIDTH / 2);
    ball.y = (WINDOW_HEIGHT / 2);
    ball.height = 15;
    ball.width = 15;

    b1.x = 20;
    b1.height = 90;
    b1.y = (WINDOW_HEIGHT / 2) - (b1.height / 2);
    b1.width = 15;


    b2.height = 90;
    b2.y = (WINDOW_HEIGHT / 2) - (b2.height / 2);
    b2.width = 15;
    b2.x = (WINDOW_WIDTH - (20 + b2.width));
}

void update(){
    int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - lastFrameTime); 
    
    if(timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME){
        SDL_Delay(timeToWait);
    }
    
    float   deltaTime = ((SDL_GetTicks() - lastFrameTime) /  1000.0f);
    
    lastFrameTime = SDL_GetTicks();

/* bolinha bater nas quinas    
    if(ball.x + ball.width >= WINDOW_WIDTH || ball.x <= 0){
        if(ball.x <= 0)
            colX = 1;
        else
            colX = -1;
    }

    if(ball.y + ball.height >= WINDOW_HEIGHT || ball.y <= 0){
        if(ball.y <= 0)
            colY = 1;
        else
            colY = -1;
    }
*/
    if(ball.x <= (b1.x + b1.width) || (ball.x + ball.width) >= b2.x)
    {  
        if(ball.y >= b1.y && ball.y <= (b1.y + b1.height)){
               colX = 1;
        }
        else if(ball.y >= b2.y && ball.y <= (b2.y + b2.height))
        {
                colX = -1;
        }else{
            ball.x = (WINDOW_WIDTH / 2);
            ball.y = (WINDOW_HEIGHT / 2);
        }
    }


    if(ball.y <= 0 || ball.y + ball.height >= WINDOW_HEIGHT){
        if(ball.y <= 0)
            colY = 1;
        else
            colY = -1;
    }

    ball.x += (90 * deltaTime) * colX;
    ball.y += (70 * deltaTime) * colY;
}


void render(){
    SDL_Event event2;
    SDL_PollEvent(&event2);
    switch (event2.type)
    {
    case SDL_KEYDOWN:
        if(event2.key.keysym.sym == SDLK_s){
            if((b1.y + b1.height) < WINDOW_HEIGHT)
                b1.y += 20;
        }
        if(event2.key.keysym.sym == SDLK_w){
            if((b1.y) > 0)
                b1.y -= 20;
        }
        if(event2.key.keysym.sym == SDLK_DOWN){
            if((b2.y + b2.height) < WINDOW_HEIGHT)
                b2.y += 20;
        }
        if(event2.key.keysym.sym == SDLK_UP){
            if((b2.y) > 0)
                b2.y -= 20;
        }
        break;
    }

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
    
    SDL_Rect bar ={ 
        b1.x,
        b1.y, 
        b1.width,
        b1.height
    };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &bar);
    
    SDL_Rect bar2 ={ 
        b2.x,
        b2.y, 
        b2.width,
        b2.height
    };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &bar2);
 


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