#ifndef TYPES_H
#define TYPES_H

// Common types shared across the project

typedef enum Boolean { FALSE = 0, TRUE = 1 } Boolean;

typedef enum Direction { UP, DOWN, LEFT, RIGHT } Direction;

// Forward declarations
typedef struct Snake Snake;
typedef struct Food Food;
typedef struct Segment Segment;

#endif // TYPES_H