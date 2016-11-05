//
//  map.c
//  labirin_trap
//
//  Created by Yana Agun Siswanto on 11/6/16.
//  Copyright © 2016 Yana Agun Siswanto. All rights reserved.
//

#include "map.h"
#include <stdlib.h>

obstacles_address allocateObstacles(position topLeft, int width, int height){
  obstacles_address oa = (obstacles_address)malloc(sizeof(obstacles));
  oa->obstacle.topLeft = topLeft;
  oa->obstacle.width   = width;
  oa->obstacle.height  = height;
  oa->next             = NULL;
  return oa;
}

void prependObstacles(map *m, obstacles *o) {
  o->next = m->obstacles;
  m->obstacles = o;
}

map createMap(WINDOW *window, obstacles *o, door _entrance, door _exit) {
  map m;
  m.obstacles = o;
  m.window    = window;
  m.entrance  = _entrance;
  m.exit      = _exit;
  return m;
}

void drawMap(map m) {
  drawDoor(m.window, m.entrance);
  drawDoor(m.window, m.exit);
  drawObstacles(m.window, m.obstacles);
  mapRefresh(m.window);
}

void drawDoor(WINDOW *win, door d) {
  switch(d.orientation) {
    case DOOR_RIGHT:
      mvwvline(win, d.position.y, d.position.x, MAP_DOOR_HORIZONTAL, d.height);
    default:
      mvwvline(win, d.position.y, d.position.x, MAP_DOOR_HORIZONTAL, d.height);
  }
}

void mapRefresh(WINDOW *win) {
    refresh();
    wrefresh(win);
}

void drawObstacles(WINDOW *win, obstacles *ob){
  obstacles_address temp = ob;
  while (1) {
    drawObstacle(win, temp->obstacle);
    if(temp->next == NULL) {
      break;
    }
    temp = temp->next;
  }
}

void drawObstacle(WINDOW *win, obstacles_rectangular ob) {
    int i;
    for(i = 0; i < ob.width; i++) {
      mvwvline(win, ob.topLeft.y, ob.topLeft.x + i, MAP_OBSTACLE, ob.height);
    }
}