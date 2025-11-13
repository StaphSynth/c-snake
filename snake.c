#include "snake.h"
#include "food.h"
#include "game.h"
#include <stdlib.h>

void initialize_snake(Snake *snake) {
    snake->head = NULL;
    snake->tail = NULL;
    snake->length = 0;
    snake->dir = RIGHT;

    for (int i = 0; i < INITIAL_SNAKE_LENGTH; i++) {
        Segment *segment = (Segment *)malloc(sizeof(Segment));
        segment->x = (WINDOW_WIDTH / 2) - (i * ELEMENT_SIZE);
        segment->y = WINDOW_HEIGHT / 2;
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
}

Snake *create_snake(void) {
    Snake *snake = (Snake *)malloc(sizeof(Snake));
    initialize_snake(snake);

    return snake;
}

void draw_snake(Snake *snake, SDL_Renderer *renderer) {
    Segment *current = snake->head;
    SDL_SetRenderDrawColor(renderer, SNAKE_COLOR_R, SNAKE_COLOR_G,
                           SNAKE_COLOR_B, SNAKE_COLOR_A);

    while (current != NULL) {
        SDL_Rect rect = {current->x, current->y, ELEMENT_SIZE, ELEMENT_SIZE};
        SDL_RenderFillRect(renderer, &rect);
        current = current->next;
    }
}

void grow_snake(Snake *snake) {
    Segment *new_segment = (Segment *)malloc(sizeof(Segment));
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

void reset_snake(Snake *snake) {
    // Free existing segments
    Segment *current = snake->head;
    Segment *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    // Reinitialize snake
    initialize_snake(snake);
}

void advance_snake(Snake *snake) {
    int dx = 0;
    int dy = 0;

    switch (snake->dir) {
    case UP:
        dy = -ELEMENT_SIZE;
        break;
    case DOWN:
        dy = ELEMENT_SIZE;
        break;
    case LEFT:
        dx = -ELEMENT_SIZE;
        break;
    case RIGHT:
        dx = ELEMENT_SIZE;
        break;
    }

    // Create new head segment
    Segment *new_head = (Segment *)malloc(sizeof(Segment));
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