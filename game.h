#include "types.h"
#include <SDL2/SDL.h>

#define ELEMENT_SIZE 20 // Size of snake segments and food in pixels
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

typedef struct SDL_handles {
    SDL_Window *window;
    SDL_Renderer *renderer;
} SDL_handles;

typedef struct GameState {
    Boolean game_over;
    Boolean quit;
    int score;
    Snake *snake;
    Food *food;
    SDL_handles *sdl_handles;
} GameState;

GameState *initialize_game(void);
void shutdown_game(GameState *game_state);
void reset_game(GameState *game_state);
void draw_game(GameState *game_state, SDL_Renderer *renderer);
void check_collisions(GameState *game_state);
void handle_input(GameState *game_state, SDL_Event *event);
