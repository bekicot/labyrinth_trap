#include "victim.h"
#include <ncurses.h>

void moveVictim(map m, victim *v, int direction) {
    int victimDirection;
    position newPosition = generateNewVictimPosition(v->position, direction, &victimDirection);
    if(!positionCollution(m, newPosition)){
        removeRenderedVictimLocation(m.window, v->position);
        v->position = newPosition;
        renderVictimLocation(m.window, v->position, victimDirection);
        mapRefresh(m.window);
    }
}

victim createVictim(map m) {
    victim v;
    position vicPosition = m.entrance.position;
    if(vicPosition.x == 0) {
        vicPosition.x++;
    } else if(vicPosition.y == 0) {
        vicPosition.y++;
    }
    v.position = vicPosition;
    renderVictimLocation(m.window, v.position, VICTIM_POSITION_RIGHT);
    mapRefresh(m.window);
    return v;
}
int positionCollution(map m, position newPosition) {
    return 0;
}

position generateNewVictimPosition(position p, int d, int *victimDirection) {
    switch(d) {
        case MOVE_UP:
            *victimDirection = VICTIM_POSITION_UP;
            p.y--;
            break;
        case MOVE_DOWN:
            *victimDirection = VICTIM_POSITION_DOWN;
            p.y++;
            break;
        case MOVE_LEFT :
            *victimDirection = VICTIM_POSITION_LEFT;
            p.x--;
            break;
        case MOVE_RIGHT :
            *victimDirection = VICTIM_POSITION_RIGHT;
            p.x++;
            break;
    }
    return p;
}

void removeRenderedVictimLocation(WINDOW *win, position p) {
    mvwaddch(win, p.y, p.x, ' ');
}

void renderVictimLocation(WINDOW *win, position p, int victimDirection) {
    mvwaddch(win, p.y, p.x, victimDirection);
}

