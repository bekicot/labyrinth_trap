#include "mapCreator.h"

void createEmptyList(list *l){
	l->first=NULL;
}

adrList alokasiList(address memoryX){
	adrList p;
	p=(adrList)malloc(sizeof(l1));
	if(p!=NULL){
		p->memory=memoryX;
	}
	return p;
}

boolean isEmptyList(list l){
	if(l.first==NULL){
		return true;
	}else{
		return false;
	}
}

void add(list *l, address memoryX){
	adrList p;
	p=alokasiList(memoryX);
	p->next=l->first;
	l->first=p;
}

boolean searchList(list l, address memoryX){
	adrList p;
	p=l.first;
	while(p!=NULL && p->memory!=memoryX){
		p=p->next;
	}
	if(p==NULL){
		return false;
	}else{
		return true;
	}
}
