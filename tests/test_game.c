#include <assert.h>
#include <stdio.h>
#include "../src/game.h"

static void prepare_frame_timing(void) {
    lastFrameTime = SDL_GetTicks() - FRAME_TARGET_TIME;
}

static void test_setup_initializes_positions(void) {
    setup();

    assert(ball.x == WINDOW_WIDTH / 2);
    assert(ball.y == WINDOW_HEIGHT / 2);
    assert(ball.width == BALL_SIZE);
    assert(ball.height == BALL_SIZE);

    assert(b1.x == PADDLE_MARGIN);
    assert(b1.width == PADDLE_WIDTH);
    assert(b1.height == PADDLE_HEIGHT);
    assert(b1.y == (WINDOW_HEIGHT / 2) - (b1.height / 2));

    assert(b2.width == PADDLE_WIDTH);
    assert(b2.height == PADDLE_HEIGHT);
    assert(b2.x == (WINDOW_WIDTH - (PADDLE_MARGIN + b2.width)));
    assert(b2.y == (WINDOW_HEIGHT / 2) - (b2.height / 2));
}

static void test_update_resets_ball_after_missing_left_paddle(void) {
    setup();
    ball.x = b1.x;
    ball.y = 0;
    colX = 0;
    colY = 0;
    prepare_frame_timing();

    update();

    assert(ball.x == WINDOW_WIDTH / 2);
    assert(ball.y == WINDOW_HEIGHT / 2);
}

static void test_update_resets_ball_after_missing_right_paddle(void) {
    setup();
    ball.x = b2.x;
    ball.y = 0;
    colX = 0;
    colY = 0;
    prepare_frame_timing();

    update();

    assert(ball.x == WINDOW_WIDTH / 2);
    assert(ball.y == WINDOW_HEIGHT / 2);
}

static void test_update_changes_vertical_direction_on_top_collision(void) {
    setup();
    colY = -1;
    ball.y = -1;
    prepare_frame_timing();

    update();

    assert(colY == 1);
}

static void test_update_changes_vertical_direction_on_bottom_collision(void) {
    setup();
    colY = 1;
    ball.y = WINDOW_HEIGHT - ball.height + 1;
    prepare_frame_timing();

    update();

    assert(colY == -1);
}

static void test_update_changes_horizontal_direction_on_left_paddle_collision(void) {
    setup();
    colX = -1;
    ball.x = b1.x + b1.width;
    ball.y = b1.y + 5;
    prepare_frame_timing();

    update();

    assert(colX == 1);
}

static void test_update_changes_horizontal_direction_on_right_paddle_collision(void) {
    setup();
    colX = 1;
    ball.x = b2.x - ball.width;
    ball.y = b2.y + 5;
    prepare_frame_timing();

    update();

    assert(colX == -1);
}

int main(void) {
    if (SDL_Init(SDL_INIT_TIMER) != 0) {
        fprintf(stderr, "Falha ao iniciar SDL no teste: %s\n", SDL_GetError());
        return 1;
    }

    test_setup_initializes_positions();
    test_update_resets_ball_after_missing_left_paddle();
    test_update_resets_ball_after_missing_right_paddle();
    test_update_changes_vertical_direction_on_top_collision();
    test_update_changes_vertical_direction_on_bottom_collision();
    test_update_changes_horizontal_direction_on_left_paddle_collision();
    test_update_changes_horizontal_direction_on_right_paddle_collision();

    SDL_Quit();
    printf("Todos os testes passaram.\n");
    return 0;
}
