#include <ncurses.h>
#include <stdio.h>
#include <ncurses.h>
#include "../map.h"
#include "../door.h"
map map_1(WINDOW *win){
  door _entrance = createDoor(createPosition(0, 1), 1, 2, DOOR_LEFT, COLOR_YELLOW);
  door _exit     = createDoor(createPosition(79, 5), 1, 4, DOOR_RIGHT, COLOR_GREEN);

  map  m  = createMap(win, allocateObstacles(createPosition(10, 0),20, 5), _entrance, _exit);

  prependObstacles(&m, allocateObstacles(createPosition(10, 7),20, 5));
  prependObstacles(&m, allocateObstacles(createPosition(10, 14),20, 5));
  prependObstacles(&m, allocateObstacles(createPosition(10, 21),20, 5));
  prependObstacles(&m, allocateObstacles(createPosition(10, 28),20, 5));
  prependObstacles(&m, allocateObstacles(createPosition(10, 35),20, 5));

  prependObstacles(&m, allocateObstacles(createPosition(32, 3),20, 5));
  prependObstacles(&m, allocateObstacles(createPosition(32, 10),20, 5));
  prependObstacles(&m, allocateObstacles(createPosition(32, 17),20, 5));
  prependObstacles(&m, allocateObstacles(createPosition(32, 23),20, 5));
  prependObstacles(&m, allocateObstacles(createPosition(32, 29),20, 5));

  prependObstacles(&m, allocateObstacles(createPosition(56, 0),20, 5));
  prependObstacles(&m, allocateObstacles(createPosition(56, 7),20, 5));
  prependObstacles(&m, allocateObstacles(createPosition(56, 14),20, 5));
  prependObstacles(&m, allocateObstacles(createPosition(56, 21),20, 5));
  prependObstacles(&m, allocateObstacles(createPosition(56, 28),20, 5));
  prependObstacles(&m, allocateObstacles(createPosition(56, 35),20, 5));

  drawMap(m);
  return m;
}
