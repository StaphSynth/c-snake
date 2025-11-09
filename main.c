#include "snake.h"
#include <SDL2/SDL.h>
#include <stdio.h>

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create window
    SDL_Window *window =
        SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create renderer
    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n",
               SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Setup game objects
    Flags game_flags;
    game_flags.food_present = FALSE;
    Snake *snake = create_snake(100, 100, INITIAL_SNAKE_LENGTH);
    Food *food = NULL;

    // Event loop
    SDL_Event e;
    int quit = 0;

    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }

            // handle keyboard input
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
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
                    quit = 1;
                    break;
                }
            }
        }

        // Clear screen with black background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (!game_flags.food_present) {
            food = create_food(snake);
            game_flags.food_present = TRUE;
        }

        draw_snake(snake, renderer);
        draw_food(food, renderer);
        advance_snake(snake);

        // Check for collisions
        if (check_self_collision(snake) || check_wall_collision(snake)) {
            quit = 1;
        } else if (check_food_collision(snake, food)) {
            grow_snake(snake);
            game_flags.food_present = FALSE;
            free_food(food);
        }

        // Present the renderer
        SDL_RenderPresent(renderer);

        SDL_Delay(100); // ~10 FPS
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    free_snake(snake);
    SDL_Quit();

    return 0;
}