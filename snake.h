#include <SDL2/SDL.h>

#define SEGMENT_SIZE 20        // Size of each snake segment in pixels
#define INITIAL_SNAKE_LENGTH 3 // Initial length of the snake in segments

#define SNAKE_COLOR_R 0   // Red component of the snake color
#define SNAKE_COLOR_G 255 // Green component of the snake color
#define SNAKE_COLOR_B 0   // Blue component of the snake color
#define SNAKE_COLOR_A 255 // Alpha component of the snake color (opacity)

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

enum { FALSE = 0, TRUE = 1 } typedef Boolean;

enum Direction { UP, DOWN, LEFT, RIGHT } typedef Direction;

struct Segment {
    int x;
    int y;
    int size;
    struct Segment *next;
} typedef Segment;

struct Snake {
    Segment *head;
    Segment *tail;
    int length;
    Direction dir;
} typedef Snake;

struct Food {
    int x;
    int y;
    int size;
} typedef Food;

struct Flags {
    Boolean food_present;
} typedef Flags;

Snake *create_snake(int start_x, int start_y, int initial_length);
void draw_snake(Snake *snake, SDL_Renderer *renderer);
void grow_snake(Snake *snake);
void free_snake(Snake *snake);
void advance_snake(Snake *snake);
void set_snake_direction(Snake *snake, Direction dir);
Boolean check_self_collision(Snake *snake);
Boolean check_wall_collision(Snake *snake);
Boolean check_food_collision(Snake *snake, Food *food);
Food *create_food(Snake *snake);
void draw_food(Food *food, SDL_Renderer *renderer);
void free_food(Food *food);
