#include "types.h"
#include <SDL2/SDL.h>

#define ELEMENT_SIZE 20 // Size of snake segments and food in pixels
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

typedef struct Flags {
    Boolean food_present;
} Flags;
