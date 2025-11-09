#include "snake.h"
#include <stdlib.h>

Snake *create_snake(int start_x, int start_y, int initial_length) {
    Snake *snake = (Snake *)malloc(sizeof(Snake));
    snake->head = NULL;
    snake->tail = NULL;
    snake->length = 0;
    snake->dir = RIGHT;

    for (int i = 0; i < initial_length; i++) {
        Segment *segment = (Segment *)malloc(sizeof(Segment));
        segment->size = SEGMENT_SIZE;
        segment->x = start_x - (i * SEGMENT_SIZE);
        segment->y = start_y;
        segment->next = NULL;

        if (snake->head == NULL) {
            snake->head = segment;
            snake->tail = segment;
        } else {
            snake->tail->next = segment;
            snake->tail = segment;
        }

        snake->length++;
    }

    return snake;
}

void draw_snake(Snake *snake, SDL_Renderer *renderer) {
    Segment *current = snake->head;
    SDL_SetRenderDrawColor(renderer, SNAKE_COLOR_R, SNAKE_COLOR_G,
                           SNAKE_COLOR_B, SNAKE_COLOR_A);

    while (current != NULL) {
        SDL_Rect rect = {current->x, current->y, current->size, current->size};
        SDL_RenderFillRect(renderer, &rect);
        current = current->next;
    }
}

void grow_snake(Snake *snake) {
    Segment *new_segment = (Segment *)malloc(sizeof(Segment));
    new_segment->size = SEGMENT_SIZE;
    new_segment->x = snake->tail->x;
    new_segment->y = snake->tail->y;
    new_segment->next = NULL;

    snake->tail->next = new_segment;
    snake->tail = new_segment;
    snake->length++;
}

void free_snake(Snake *snake) {
    Segment *current = snake->head;
    Segment *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(snake);
}

void advance_snake(Snake *snake) {
    int dx = 0;
    int dy = 0;

    switch (snake->dir) {
    case UP:
        dy = -SEGMENT_SIZE;
        break;
    case DOWN:
        dy = SEGMENT_SIZE;
        break;
    case LEFT:
        dx = -SEGMENT_SIZE;
        break;
    case RIGHT:
        dx = SEGMENT_SIZE;
        break;
    }

    // Create new head segment
    Segment *new_head = (Segment *)malloc(sizeof(Segment));
    new_head->size = SEGMENT_SIZE;
    new_head->x = snake->head->x + dx;
    new_head->y = snake->head->y + dy;
    new_head->next = snake->head;

    // Update snake head
    snake->head = new_head;
    snake->length++;

    // Remove tail segment
    Segment *current = snake->head;
    while (current->next != snake->tail) {
        current = current->next;
    }

    free(snake->tail);
    current->next = NULL;
    snake->tail = current;
    snake->length--;
}

void set_snake_direction(Snake *snake, Direction dir) {
    switch (snake->dir) {
    case UP:
        if (dir == DOWN)
            return;
        break;
    case DOWN:
        if (dir == UP)
            return;
        break;
    case LEFT:
        if (dir == RIGHT)
            return;
        break;
    case RIGHT:
        if (dir == LEFT)
            return;
        break;
    }

    snake->dir = dir;
}

Boolean check_self_collision(Snake *snake) {
    Segment *head = snake->head;
    Segment *current = head->next;

    // walk the snake segments to see if head collides with any
    while (current != NULL) {
        if (head->x == current->x && head->y == current->y) {
            return TRUE;
        }
        current = current->next;
    }

    return FALSE;
}

Boolean check_wall_collision(Snake *snake) {
    Segment *head = snake->head;

    if (head->x < 0 || head->x >= WINDOW_WIDTH || head->y < 0 ||
        head->y >= WINDOW_HEIGHT) {
        return TRUE;
    }

    return FALSE;
}

Food *create_food(Snake *snake) {
    Food *food = (Food *)malloc(sizeof(Food));
    food->size = SEGMENT_SIZE;

    // Place food in a random position not occupied by the snake
    int valid_position = 0;
    while (!valid_position) {
        food->x = (rand() % (WINDOW_WIDTH / SEGMENT_SIZE)) * SEGMENT_SIZE;
        food->y = (rand() % (WINDOW_HEIGHT / SEGMENT_SIZE)) * SEGMENT_SIZE;

        // Check if the food position collides with the snake
        Segment *current = snake->head;
        valid_position = 1;
        while (current != NULL) {
            if (current->x == food->x && current->y == food->y) {
                valid_position = 0;
                break;
            }
            current = current->next;
        }
    }

    return food;
}

void draw_food(Food *food, SDL_Renderer *renderer) {
    if (food == NULL)
        return;

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color for food
    SDL_Rect rect = {food->x, food->y, food->size, food->size};
    SDL_RenderFillRect(renderer, &rect);
}

void free_food(Food *food) { free(food); }

Boolean check_food_collision(Snake *snake, Food *food) {
    if (food == NULL) {
        return FALSE;
    }

    Segment *head = snake->head;

    if (head->x == food->x && head->y == food->y) {
        return TRUE;
    }

    return FALSE;
}