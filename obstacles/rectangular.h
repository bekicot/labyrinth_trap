#ifndef rectangular_h
#define rectangular_h

#include "../position.h"

typedef struct ObstacleRectangular *obstacle_rectangular_address;

typedef struct ObstacleRectangular {
    int width;
    int height;
    position topLeft;
} obstacles_rectangular;

obstacles_rectangular obstacle_rectangular_create(int position, int width, int height);

#endif /* rectangular_h */
