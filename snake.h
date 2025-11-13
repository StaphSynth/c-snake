#include "types.h"
#include <SDL2/SDL.h>

#define INITIAL_SNAKE_LENGTH 3 // Initial length of the snake in segments

#define SNAKE_COLOR_R 0   // Red component of the snake color
#define SNAKE_COLOR_G 255 // Green component of the snake color
#define SNAKE_COLOR_B 0   // Blue component of the snake color
#define SNAKE_COLOR_A 255 // Alpha component of the snake color (opacity)

struct Segment {
    int x;
    int y;
    struct Segment *next;
};

struct Snake {
    Segment *head;
    Segment *tail;
    int length;
    Direction dir;
};

Snake *create_snake(void);
void draw_snake(Snake *snake, SDL_Renderer *renderer);
void grow_snake(Snake *snake);
void free_snake(Snake *snake);
void advance_snake(Snake *snake);
void set_snake_direction(Snake *snake, Direction dir);
void reset_snake(Snake *snake);
Boolean check_self_collision(Snake *snake);
Boolean check_wall_collision(Snake *snake);
Boolean check_food_collision(Snake *snake, Food *food);
