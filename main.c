#include "food.h"
#include "game.h"
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
    GameState *game_state = initialize_game();
    Snake *snake = game_state->snake;
    Food *food = game_state->food;

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

        draw_game(game_state, renderer);
        advance_snake(snake);
        check_collisions(game_state);

        // Present the renderer
        SDL_RenderPresent(renderer);

        SDL_Delay(100); // ~10 FPS
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    shutdown_game(game_state);
    SDL_Quit();

    return 0;
}