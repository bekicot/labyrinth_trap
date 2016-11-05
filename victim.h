#ifndef victim_h
#define victim_h

#include <stdio.h>
#include <ncurses.h>
#include "position.h"
#include "map.h"

#define MOVE_UP    0
#define MOVE_RIGHT 1
#define MOVE_DOWN  2
#define MOVE_LEFT  4

#define VICTIM_POSITION_UP      ACS_UARROW
#define VICTIM_POSITION_DOWN    ACS_DARROW
#define VICTIM_POSITION_LEFT    ACS_LARROW
#define VICTIM_POSITION_RIGHT   ACS_RARROW

typedef struct Victim
{
    position position;
} victim;

void moveVictim(map m, victim *v, int direction);
victim createVictim(map m);
int positionCollution(map m, position newPosition);
position generateNewVictimPosition(position p, int d, int *victimDirection);
void removeRenderedVictimLocation(WINDOW *window, position p);
void renderVictimLocation(WINDOW *win, position p, int victimDirection);

#endif /* victim_h */
