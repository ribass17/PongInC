#ifndef SDL_COMPAT_H
#define SDL_COMPAT_H

#ifdef UNIT_TEST
#include <stdint.h>

typedef uint32_t Uint32;

typedef struct SDL_Window SDL_Window;
typedef struct SDL_Renderer SDL_Renderer;

typedef struct {
    int sym;
} SDL_Keysym;

typedef struct {
    SDL_Keysym keysym;
} SDL_KeyboardEvent;

typedef struct {
    int type;
    SDL_KeyboardEvent key;
} SDL_Event;

typedef struct {
    int x, y, w, h;
} SDL_Rect;

#define SDL_INIT_EVERYTHING 0
#define SDL_INIT_TIMER 0
#define SDL_QUIT 0x100
#define SDL_KEYDOWN 0x300
#define SDLK_ESCAPE 27
#define SDLK_s 's'
#define SDLK_w 'w'
#define SDLK_DOWN 274
#define SDLK_UP 273
#define SDL_WINDOWPOS_CENTERED 0

int SDL_Init(Uint32 flags);
const char* SDL_GetError(void);
SDL_Window* SDL_CreateWindow(const char* title, int x, int y, int w, int h, Uint32 flags);
SDL_Renderer* SDL_CreateRenderer(SDL_Window* window, int index, Uint32 flags);
int SDL_PollEvent(SDL_Event* event);
Uint32 SDL_GetTicks(void);
void SDL_Delay(Uint32 ms);
int SDL_SetRenderDrawColor(SDL_Renderer* renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
int SDL_RenderClear(SDL_Renderer* renderer);
int SDL_RenderFillRect(SDL_Renderer* renderer, const SDL_Rect* rect);
void SDL_RenderPresent(SDL_Renderer* renderer);
void SDL_DestroyRenderer(SDL_Renderer* renderer);
void SDL_DestroyWindow(SDL_Window* window);
void SDL_Quit(void);

#else
#include <SDL2/SDL.h>
#endif

#endif
