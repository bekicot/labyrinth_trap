#ifndef position_h
#define position_h

#include <stdio.h>

struct Position {
    int x;
    int y;
};

typedef struct Position position;

position createPosition(int x, int y);

#endif /* position_h */
