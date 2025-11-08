#include <stdlib.h>
#include "snake.h"

Snake* create_snake(int start_x, int start_y, int initial_length) {
    Snake* snake = (Snake*)malloc(sizeof(Snake));
    snake->head = NULL;
    snake->tail = NULL;
    snake->length = 0;

    for (int i = 0; i < initial_length; i++) {
        Segment* segment = (Segment*)malloc(sizeof(Segment));
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

void draw_snake(Snake* snake, SDL_Renderer* renderer) {
    Segment* current = snake->head;
    SDL_SetRenderDrawColor(renderer,
                          SNAKE_COLOR_R,
                          SNAKE_COLOR_G,
                          SNAKE_COLOR_B,
                          SNAKE_COLOR_A);

    while (current != NULL) {
        SDL_Rect rect = {current->x, current->y, current->size, current->size};
        SDL_RenderFillRect(renderer, &rect);
        current = current->next;
    }
}

void grow_snake(Snake* snake) {
    Segment* new_segment = (Segment*)malloc(sizeof(Segment));
    new_segment->size = SEGMENT_SIZE;
    new_segment->x = snake->tail->x;
    new_segment->y = snake->tail->y;
    new_segment->next = NULL;

    snake->tail->next = new_segment;
    snake->tail = new_segment;
    snake->length++;
}

void free_snake(Snake* snake) {
    Segment* current = snake->head;
    Segment* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(snake);
}

void advance_snake(Snake* snake, int dx, int dy) {
    // Create new head segment
    Segment* new_head = (Segment*)malloc(sizeof(Segment));
    new_head->size = SEGMENT_SIZE;
    new_head->x = snake->head->x + dx;
    new_head->y = snake->head->y + dy;
    new_head->next = snake->head;

    // Update snake head
    snake->head = new_head;
    snake->length++;

    // Remove tail segment
    Segment* current = snake->head;
    while (current->next != snake->tail) {
        current = current->next;
    }
    free(snake->tail);
    current->next = NULL;
    snake->tail = current;
    snake->length--;
}