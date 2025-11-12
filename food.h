#include "types.h"
#include <SDL2/SDL.h>

struct Food {
    int x;
    int y;
    int size;
};

Food *create_food(Snake *snake);
void draw_food(Food *food, SDL_Renderer *renderer);
void free_food(Food *food);