//
//  map.h
//  labirin_trap
//
//  Created by Yana Agun Siswanto on 11/6/16.
//  Copyright © 2016 Yana Agun Siswanto. All rights reserved.
//

#ifndef map_h
#define map_h

#include <stdio.h>
#include <ncurses.h>
#include "obstacles/rectangular.h"
#include "door.h"
#define MAP_HEIGHT  40
#define MAP_WIDTH   80
// #define MAP_DOOR    0x2588
#define MAP_DOOR_HORIZONTAL    'X'
#define MAP_DOOR_VERTICAL      'X'
#define MAP_OBSTACLE           '#'

typedef struct Obstacles *obstacles_address;

typedef struct Obstacles {
    obstacles_rectangular obstacle;
    obstacles_address next;
} obstacles;

typedef struct ObstaclesList {
  obstacles_address first;
} obstacles_list;

typedef struct Map {
  WINDOW *window;
  obstacles_address obstacles;
  door entrance;
  door exit;
} map;

obstacles_address allocateObstacles(position topLeft, int width, int height);
void prependObstacles(map *m, obstacles *o);
map createMap(WINDOW *window, obstacles *o, door _entrance, door _exit);
void drawMap(map m);
void drawDoor(WINDOW *win, door d);
void mapRefresh(WINDOW *win);
void drawObstacles(WINDOW *win, obstacles_address ob);
void drawObstacle(WINDOW *win, obstacles_rectangular ob);

#endif /* map_h */
