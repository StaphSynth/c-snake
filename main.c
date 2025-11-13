#include "food.h"
#include "game.h"
#include "snake.h"
#include <SDL2/SDL.h>
#include <stdio.h>

int main() {
    // setup
    GameState *game_state = initialize_game();
    Snake *snake = game_state->snake;
    SDL_Renderer *renderer = game_state->sdl_handles->renderer;
    SDL_Event e;

    // main game loop
    while (!game_state->quit) {
        // Handle events
        while (SDL_PollEvent(&e)) {
            handle_input(game_state, &e);
        }

        draw_game(game_state, renderer);
        advance_snake(snake);
        check_collisions(game_state);

        // Present the renderer
        SDL_RenderPresent(renderer);

        SDL_Delay(100); // ~10 FPS
    }

    shutdown_game(game_state);
    return 0;
}