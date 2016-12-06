#include "stdio.h"
#include "stdlib.h"
#include "boolean.h"
#ifndef mapCreator_H
#define mapCreator_H

typedef struct{
	int x;
	int y;
}coordinate;

typedef struct elmtSubMap *address;

typedef struct elmtSubMap{
	coordinate position;
	address top;
	address bottom;
	address left;
	address right;
}pixel;

typedef struct{
	address activePixel;
	address in;
	address out;
	int length;
	int width;
}map;

void createEmptyMap(map *m, int lengthX, int widthX);
address createPixel(int X, int Y, address topX, address bottomX, address leftX, address rightX);
void createIn(map *m, int X, int Y);
void setOut(map *m, address outX);
address search(address p, int X, int Y); // P.S : belum dicoba dalam semua kondisi, hanya sukses untuk pencarian in, dan satu pixel disekitar in
void addTop(map *m, int cX, int cY); // P.S : masih kurang pengujian apakah cX dan cY sudah ada dan apakah memungkinkan melakukan penambahan bila sudah berada di sisi terluar peta
void addBottom(map *m, int cX, int cY); // P.S : masih kurang pengujian apakah cX dan cY sudah ada dan apakah memungkinkan melakukan penambahan bila sudah berada di sisi terluar peta
void addLeft(map *m, int cX, int cY); // P.S : masih kurang pengujian apakah cX dan cY sudah ada dan apakah memungkinkan melakukan penambahan bila sudah berada di sisi terluar peta
void addRight(map *m, int cX, int cY); // P.S : masih kurang pengujian apakah cX dan cY sudah ada dan apakah memungkinkan melakukan penambahan bila sudah berada di sisi terluar peta
#endif
