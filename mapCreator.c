#include "mapCreator.h"

void createEmptyMap(map *m, int lengthX, int widthX){
	m->length=lengthX;
	m->width=widthX;
	m->activePixel=NULL;
	m->in=NULL;
	m->out=NULL;
}

address createPixel(int X, int Y, address topX, address bottomX, address leftX, address rightX){
	address p;
	p=(address)malloc(sizeof(pixel));
	if(p!=NULL){
		p->position.x=X;
		p->position.y=Y;
		p->top=topX;
		p->bottom=bottomX;
		p->left=leftX;
		p->right=rightX;
	}
	return p;
}

void createIn(map *m, int X, int Y){
	if(X > m->length-1 || Y > m->width-1){
		printf("\n!!! (x) atau (y) yang anda masukkan melebihi batas\n");
	}else{
		m->in=createPixel(X, Y, NULL, NULL, NULL, NULL);
		printf("\nPintu masuk telah disiapkan");
	}
}

void setOut(map *m, address outX){
	m->out=outX;
}

address search(address p, int X, int Y){
	address pt, pb, pl, pr;
	if(p==NULL){
		return NULL;
	}else{
		pt=p->top;
		pb=p->bottom;
		pl=p->left;
		pr=p->right;
		if(p->position.x == X && p->position.y == Y){
			return p;
		}else{
			if( (search(pt, X, Y) != NULL) || (search(pb, X, Y) != NULL) || (search(pl, X, Y) != NULL) || (search(pr, X, Y) != NULL) ){
				if((search(pt, X, Y) != NULL)){
					return pt;
				}else{
					if((search(pb, X, Y) != NULL)){
						return pb;
					}else{
						if((search(pl, X, Y) != NULL)){
							return pl;
						}else{
							if((search(pr, X, Y) != NULL)){
								return pr;
							}
						}
					}
				}
			}else{
				return NULL;
			}
		}
	}
}

void addTop(map *m, int cX, int cY){
	if(m->in!=NULL){
		search(m->in, cX, cY)->top=createPixel(cX, cY-1, NULL, search(m->in, cX, cY), NULL, NULL);
	}
}

void addBottom(map *m, int cX, int cY){
	if(m->in!=NULL){
		search(m->in, cX, cY)->bottom=createPixel(cX, cY+1, search(m->in, cX, cY), NULL, NULL, NULL);
	}
}

void addLeft(map *m, int cX, int cY){
	if(m->in!=NULL){
		search(m->in, cX, cY)->left=createPixel(cX-1, cY, NULL, NULL, search(m->in, cX, cY), NULL);
	}
}

void addRight(map *m, int cX, int cY){
	if(m->in!=NULL){
		search(m->in, cX, cY)->right=createPixel(cX+1, cY, NULL, NULL, NULL, search(m->in, cX, cY));
	}
}
