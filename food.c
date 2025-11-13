#include "food.h"
#include "game.h"
#include "snake.h"

void draw_food(Food *food, SDL_Renderer *renderer) {
    if (food == NULL || !food->visible)
        return;

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color for food
    SDL_Rect rect = {food->x, food->y, ELEMENT_SIZE, ELEMENT_SIZE};
    SDL_RenderFillRect(renderer, &rect);
}

void free_food(Food *food) { free(food); }

Food *create_food(void) {
    Food *food = (Food *)malloc(sizeof(Food));
    food->visible = FALSE;

    return food;
}

void eat_food(Food *food) { food->visible = FALSE; }

void place_food(Food *food, Snake *snake) {
    if (food == NULL || snake == NULL)
        return;

    // Place food in a random position not occupied by the snake
    int valid_position = FALSE;
    while (!valid_position) {
        food->x = (rand() % (WINDOW_WIDTH / ELEMENT_SIZE)) * ELEMENT_SIZE;
        food->y = (rand() % (WINDOW_HEIGHT / ELEMENT_SIZE)) * ELEMENT_SIZE;

        // Check if the position collides with the snake
        Segment *current = snake->head;
        valid_position = TRUE;
        while (current != NULL) {
            if (current->x == food->x && current->y == food->y) {
                valid_position = FALSE;
                break;
            }
            current = current->next;
        }
    }

    food->visible = TRUE;
}