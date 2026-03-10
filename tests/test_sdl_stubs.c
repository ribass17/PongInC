#include "../src/sdl_compat.h"

struct SDL_Window {};
struct SDL_Renderer {};

static Uint32 fake_ticks = 1000;

int SDL_Init(Uint32 flags) {
    (void)flags;
    return 0;
}

const char* SDL_GetError(void) {
    return "stub";
}

SDL_Window* SDL_CreateWindow(const char* title, int x, int y, int w, int h, Uint32 flags) {
    (void)title; (void)x; (void)y; (void)w; (void)h; (void)flags;
    static struct SDL_Window window;
    return &window;
}

SDL_Renderer* SDL_CreateRenderer(SDL_Window* window, int index, Uint32 flags) {
    (void)window; (void)index; (void)flags;
    static struct SDL_Renderer renderer;
    return &renderer;
}

int SDL_PollEvent(SDL_Event* event) {
    if (event) {
        event->type = -1;
    }
    return 0;
}

Uint32 SDL_GetTicks(void) {
    fake_ticks += 16;
    return fake_ticks;
}

void SDL_Delay(Uint32 ms) {
    (void)ms;
}

int SDL_SetRenderDrawColor(SDL_Renderer* renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    (void)renderer; (void)r; (void)g; (void)b; (void)a;
    return 0;
}

int SDL_RenderClear(SDL_Renderer* renderer) {
    (void)renderer;
    return 0;
}

int SDL_RenderFillRect(SDL_Renderer* renderer, const SDL_Rect* rect) {
    (void)renderer; (void)rect;
    return 0;
}

void SDL_RenderPresent(SDL_Renderer* renderer) {
    (void)renderer;
}

void SDL_DestroyRenderer(SDL_Renderer* renderer) {
    (void)renderer;
}

void SDL_DestroyWindow(SDL_Window* window) {
    (void)window;
}

void SDL_Quit(void) {}
