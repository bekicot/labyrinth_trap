#include "stdio.h"
#include "stdlib.h"
#include "boolean.h"
#ifndef mapCreator_H
#define mapCreator_H

typedef struct{
	int row;
	int column;
}coordinate;

typedef struct{
	char on="o";
	char off=" ";
}character1;

typedef struct{
	char on="x";
	char off=" ";
}character2;

typedef struct elmtSubMap *address;

typedef struct elmtSubMap{
	coordinate position;
	character1 player;
	character2 npc;
	boolean passable;
	address top;
	address bottom;
	address left;
	address right;
}pixel;

typedef address map;

void createPixel(map *m, int rowX, int columnX, address top, address bottom, address left, address right);
// I.S : map is NULL
// F.S : create a pixel

address searchPixel(map m, int rowX, int columnX, int length, int width);
// I.S : map might be empty
// I.S : pixel(rowX, columnX) might be not on the map
// I.S : pixel(rowX, columnX) might be on the map
// F.S : return an address of a pixel

void createMap(map *m, int rowX, int columnX, int length, int width);
// I.S : *m is NULL
// I.S : rowX is "0" and columnX is "0"
// F.S : create a map with fixed size (length*width)

void createObstacle(map *m, int rowLTC, int columnLTC, int length, int width);
// I.S : map might be empty
// I.S : map might be not empty
// I.S : LTC (Left-Top Corner) position must be avaiable on the map
// I.S : obstacle size should not over the map size
// F.S : change a block of pixel's passable-property from "FALSE" to "TRUE"

#endif