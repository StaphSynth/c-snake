#include "game.h"
#include "food.h"
#include "snake.h"
#include <SDL2/SDL.h>

SDL_handles *initialize_sdl(void) {
    SDL_handles *sdl_handles = (SDL_handles *)malloc(sizeof(SDL_handles));

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Window *window = SDL_CreateWindow("Snake in C", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                          WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n",
               SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    sdl_handles->window = window;
    sdl_handles->renderer = renderer;

    return sdl_handles;
}

GameState *initialize_game(void) {
    GameState *game_state = (GameState *)malloc(sizeof(GameState));
    game_state->game_over = FALSE;
    game_state->quit = FALSE;
    game_state->score = 0;
    game_state->snake = create_snake();
    game_state->food = create_food();
    game_state->sdl_handles = initialize_sdl();

    place_food(game_state->food, game_state->snake);

    return game_state;
}

void shutdown_game(GameState *game_state) {
    // Free snake and food
    free_snake(game_state->snake);
    free_food(game_state->food);

    // cleanup SDL & game_state
    SDL_DestroyRenderer(game_state->sdl_handles->renderer);
    SDL_DestroyWindow(game_state->sdl_handles->window);
    free(game_state->sdl_handles);
    free(game_state);

    SDL_Quit();
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

void handle_input(GameState *game_state, SDL_Event *event) {
    Snake *snake = game_state->snake;

    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
        case SDLK_UP:
            set_snake_direction(snake, UP);
            break;
        case SDLK_DOWN:
            set_snake_direction(snake, DOWN);
            break;
        case SDLK_LEFT:
            set_snake_direction(snake, LEFT);
            break;
        case SDLK_RIGHT:
            set_snake_direction(snake, RIGHT);
            break;
        case SDLK_ESCAPE:
            game_state->quit = TRUE;
            break;
        case SDL_QUIT:
            game_state->quit = TRUE;
            break;
        }
    }
}
