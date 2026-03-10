#ifndef GAME_H
#define GAME_H

#include "./sdl_compat.h"
#include "./constants.h"

extern int gameIsRunning;
extern int colX;
extern int colY;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern int lastFrameTime;

struct ball {
    float x, y, width, height;
};

extern struct ball ball;

typedef struct {
    float x, y, width, height;
} barra;

extern barra b1, b2;

int initializeWindow(void);
void processInput(void);
void setup(void);
void update(void);
void render(void);
void stopGame(void);

#endif
