#include "game.h"
#include "food.h"
#include "snake.h"

GameState *initialize_game(void) {
    GameState *game_state = (GameState *)malloc(sizeof(GameState));
    game_state->game_over = FALSE;
    game_state->snake = create_snake();
    game_state->food = create_food();

    place_food(game_state->food, game_state->snake);

    return game_state;
}

void shutdown_game(GameState *game_state) {
    free_snake(game_state->snake);

    if (game_state->food != NULL)
        free_food(game_state->food);

    free(game_state);
}

void reset_game(GameState *game_state) {
    game_state->game_over = FALSE;
    game_state->score = 0;

    reset_snake(game_state->snake);

    game_state->food->visible = FALSE;
    place_food(game_state->food, game_state->snake);
}

void draw_game(GameState *game_state, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    draw_snake(game_state->snake, renderer);
    draw_food(game_state->food, renderer);
}

void check_collisions(GameState *game_state) {
    Snake *snake = game_state->snake;
    Food *food = game_state->food;

    if (check_self_collision(snake) || check_wall_collision(snake)) {
        // game_state->game_over = TRUE;
        reset_game(game_state);
    } else if (check_food_collision(snake, food)) {
        grow_snake(snake);
        eat_food(food);
        place_food(food, snake);
        game_state->score += 10;
    }
}