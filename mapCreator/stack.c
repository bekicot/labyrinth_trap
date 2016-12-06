#include "mapCreator.h"

void createEmptyStack(stack *s){
	s->topStack=NULL;
}

adrStack alokasiStack(address memoryX){
	adrStack p;
	p=(adrStack)malloc(sizeof(s1));
	if(p!=NULL){
		p->memory=memoryX;
		p->next=NULL;
	}
	return p;
}

boolean isEmptyStack(stack s){
	if(s.topStack==NULL){
		return true;
	}else{
		return false;
	}
}

void push(stack *s, address memoryX){
	adrStack p;
	p=alokasiStack(memoryX);
	p->next=s->topStack;
	s->topStack=p;
}

void pop(stack *s, address memoryX){
	adrStack p;
	if(!isEmptyStack(*s)){
		p=s->topStack;
		memoryX=p->memory;
		s->topStack=p->next;
		p->next=NULL;
		free(p);
	}
}
