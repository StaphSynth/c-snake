#include "types.h"
#include <SDL2/SDL.h>

struct Food {
    int x;
    int y;
    Boolean visible;
};

Food *create_food(void);
void draw_food(Food *food, SDL_Renderer *renderer);
void free_food(Food *food);
void place_food(Food *food, Snake *snake);
void eat_food(Food *food);