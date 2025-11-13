#include "types.h"
#include <SDL2/SDL.h>

#define ELEMENT_SIZE 20 // Size of snake segments and food in pixels
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

typedef struct GameState {
    Boolean game_over;
    int score;
    Snake *snake;
    Food *food;
} GameState;

GameState *initialize_game(void);
void shutdown_game(GameState *game_state);
void reset_game(GameState *game_state);
void draw_game(GameState *game_state, SDL_Renderer *renderer);
void check_collisions(GameState *game_state);
