#ifndef door_h
#define door_h

#include "position.h"

#define DOOR_TOP    0
#define DOOR_RIGHT  1
#define DOOR_BOTTOM 2
#define DOOR_LEFT   3

typedef struct Door {
    int      width;
    int      height;
    position position;
    int      orientation;
    int      color;
} door;

door createDoor(position position, int width, int height, int orientation, int color);

#endif