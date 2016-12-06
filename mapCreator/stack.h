#include "stdio.h"
#include "stdlib.h"
#include "boolean.h"
#include "mapCreator.h"
#ifndef stack_H
#define stack_H

typedef struct elmtStack *adrStack;
typedef struct elmtStack{
	address memory;
	adrStack next;
}s1;
typedef struct{
	adrStack topStack;
}stack;

void createEmptyStack(stack *s);
adrStack alokasiStack(address memoryX);
boolean isEmptyStack(stack s);
void push(stack *s, address memoryX);
void pop(stack *s, address memoryX);

#endif
