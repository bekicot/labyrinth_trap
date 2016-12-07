#include "stdio.h"
#include "stdlib.h"
#include "boolean.h"
#ifndef mapCreator_H
#define mapCreator_H

//mapCreator

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

//mapCreator
//stack

typedef struct elmtStack *adrStack;
typedef struct elmtStack{
	address memory;
	adrStack next;
}s1;
typedef struct{
	adrStack topStack;
}stack;


//stack
//list

typedef struct elmtList *adrList;
typedef struct elmtList{
	address memory;
	adrList next;
}l1;
typedef struct{
	adrList first;
}list;

//list
//stack

void createEmptyStack(stack *s);
adrStack alokasiStack(address memoryX);
boolean isEmptyStack(stack s);
void push(stack *s, address memoryX);
void pop(stack *s, address memoryX);

//stack
//list

void createEmptyList(list *l);
adrList alokasiList(address memoryX);
boolean isEmptyList(list l);
void add(list *l, address memoryX);
boolean searchList(list l, address memoryX);

//list
//mapCreator

void createEmptyMap(map *m, int lengthX, int widthX);
address createPixel(int X, int Y, address topX, address bottomX, address leftX, address rightX);
void createIn(map *m, int X, int Y);
void setOut(map *m, address outX);
void connect(address a, address b);
boolean isIntersection(address pixelX);
boolean isEnd(list l, address pixelX); // pastikan pixelX tidak akan pernah NULL
boolean isPassed(list l, address pixelX);
address pixelSearch(list *sudahDilewati, address pixel, int x, int y);
address search(map m, int X, int Y); // pastikan map tidak kosong
void addTop(map *m, int Xpredessor, int Ypredessor);
void addBottom(map *m, int Xpredessor, int Ypredessor);
void addLeft(map *m, int Xpredessor, int Ypredessor);
void addRight(map *m, int Xpredessor, int Ypredessor);
void showMap(map *m);

//mapCreator

#endif
