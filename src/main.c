#include <stdio.h>
#include "./game.h"

int gameIsRunning = FALSE;
int colX = 1;
int colY = 1;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int lastFrameTime = 0;

struct ball ball;
barra b1, b2;

int initializeWindow(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
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
    if (!window) {
        fprintf(stderr, "Erro ao criar janela no SDL.\n");
        return FALSE;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Erro ao criar renderizacao.\n");
        return FALSE;
    }

    return TRUE;
}

void processInput(void) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            gameIsRunning = FALSE;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                gameIsRunning = FALSE;
            else if (event.key.keysym.sym == SDLK_s) {
                if ((b1.y + b1.height) < WINDOW_HEIGHT)
                    b1.y += PADDLE_SPEED;
            } else if (event.key.keysym.sym == SDLK_w) {
                if (b1.y > 0)
                    b1.y -= PADDLE_SPEED;
            } else if (event.key.keysym.sym == SDLK_DOWN) {
                if ((b2.y + b2.height) < WINDOW_HEIGHT)
                    b2.y += PADDLE_SPEED;
            } else if (event.key.keysym.sym == SDLK_UP) {
                if (b2.y > 0)
                    b2.y -= PADDLE_SPEED;
            }
            break;
        }
    }
}

void setup(void) {
    ball.x = (WINDOW_WIDTH / 2);
    ball.y = (WINDOW_HEIGHT / 2);
    ball.height = BALL_SIZE;
    ball.width = BALL_SIZE;

    b1.x = PADDLE_MARGIN;
    b1.height = PADDLE_HEIGHT;
    b1.y = (WINDOW_HEIGHT / 2) - (b1.height / 2);
    b1.width = PADDLE_WIDTH;

    b2.height = PADDLE_HEIGHT;
    b2.y = (WINDOW_HEIGHT / 2) - (b2.height / 2);
    b2.width = PADDLE_WIDTH;
    b2.x = (WINDOW_WIDTH - (PADDLE_MARGIN + b2.width));
}

void update(void) {
    int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - lastFrameTime);

    if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) {
        SDL_Delay(timeToWait);
    }

    float deltaTime = ((SDL_GetTicks() - lastFrameTime) / 1000.0f);

    lastFrameTime = SDL_GetTicks();

    /* Colisao com a raquete esquerda */
    if (ball.x <= (b1.x + b1.width)) {
        if (ball.y + ball.height >= b1.y && ball.y <= (b1.y + b1.height)) {
            colX = 1;
        } else {
            ball.x = (WINDOW_WIDTH / 2);
            ball.y = (WINDOW_HEIGHT / 2);
        }
    }

    /* Colisao com a raquete direita */
    if ((ball.x + ball.width) >= b2.x) {
        if (ball.y + ball.height >= b2.y && ball.y <= (b2.y + b2.height)) {
            colX = -1;
        } else {
            ball.x = (WINDOW_WIDTH / 2);
            ball.y = (WINDOW_HEIGHT / 2);
        }
    }

    /* Colisao com topo e fundo */
    if (ball.y <= 0 || ball.y + ball.height >= WINDOW_HEIGHT) {
        if (ball.y <= 0)
            colY = 1;
        else
            colY = -1;
    }

    ball.x += (BALL_SPEED_X * deltaTime) * colX;
    ball.y += (BALL_SPEED_Y * deltaTime) * colY;
}

void render(void) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect ballRect = {
        (int)ball.x,
        (int)ball.y,
        (int)ball.width,
        (int)ball.height
    };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &ballRect);

    SDL_Rect bar = {
        (int)b1.x,
        (int)b1.y,
        (int)b1.width,
        (int)b1.height
    };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &bar);

    SDL_Rect bar2 = {
        (int)b2.x,
        (int)b2.y,
        (int)b2.width,
        (int)b2.height
    };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &bar2);

    SDL_RenderPresent(renderer);
}

void stopGame(void) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

#ifndef UNIT_TEST
int main(void) {
    gameIsRunning = initializeWindow();

    setup();

    while (gameIsRunning) {
        processInput();
        update();
        render();
    }

    stopGame();

    return 0;
}
#endif