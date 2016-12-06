#include "stdio.h"
#include "stdlib.h"
#include "boolean.h"
#include "mapCreator.h"
#ifndef list_H
#define list_H

typedef struct elmtList *adrList;
typedef struct elmtList{
	address memory;
	adrList next;
}l1;
typedef struct{
	adrList first;
}list;

void createEmptyList(list *l);
adrList alokasiList(address memoryX);
boolean isEmptyList(list l);
void add(list *l, address memoryX);
boolean searchList(list l, address memoryX);
#endif
