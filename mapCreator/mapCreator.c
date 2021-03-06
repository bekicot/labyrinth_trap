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
	if(m->in!=NULL){
	}else{
		if(X > m->length-1 || Y > m->width-1){
		}else{
			m->in=createPixel(X, Y, NULL, NULL, NULL, NULL);
		}
	}
}

void setOut(map *m, address outX){
	if(outX == NULL){
	}else{
		m->out=outX;
	}
}

void connect(address a, address b){
	if(a!=NULL && b!=NULL){
		if(a->position.x == b->position.x){
			if(a->position.y == b->position.y-1){
				a->top=b;
				b->bottom=a;
			}else{
				if(a->position.y == b->position.y+1){
					a->bottom=b;
					b->top=a;
				}else{
				}
			}
		}else{
			if(a->position.y == b->position.y){
				if(a->position.x == b->position.x-1){
					a->right=b;
					b->left=a;
				}else{
					if(a->position.x == b->position.x+1){
						a->left=b;
						b->right=a;
					}else{
					}
				}
			}else{
			}
		}
	}else{
		if(a == NULL){
		}
		if(b == NULL){
		}
	}
}

boolean isIntersection(address pixelX){
	int counter=0;
	if(pixelX==NULL){
		return false;
	}else{
		if(pixelX->top!=NULL){
			counter=counter+1;
		}
		if(pixelX->bottom!=NULL){
			counter=counter+1;
		}
		if(pixelX->left!=NULL){
			counter=counter+1;
		}
		if(pixelX->right!=NULL){
			counter=counter+1;
		}
		if(counter<3){
			return false;
		}else{
			return true;
		}
	}
}

boolean isEnd(list l, address pixelX){
	boolean b1,b2,b3,b4,B;
	b1=false;
	b2=false;
	b3=false;
	b4=false;
	if(pixelX==NULL){
		return true;
	}else{
		if(l.first==NULL){
			if( (pixelX->top != NULL) || (pixelX->bottom != NULL) || (pixelX->left != NULL) || (pixelX->right != NULL) ){
				return false;
			}else{
				return true;
			}
		}else{
			if( (pixelX->top != NULL) || (pixelX->bottom != NULL) || (pixelX->left != NULL) || (pixelX->right != NULL) ){
				if(pixelX->top != NULL){
					if(searchList(l, pixelX->top)){
						b1=true;
					}
				}
				if(pixelX->bottom != NULL){
					if(searchList(l, pixelX->bottom)){
						b2=true;
					}
				}
				if(pixelX->left != NULL){
					if(searchList(l, pixelX->left)){
						b3=true;
					}
				}
				if(pixelX->right != NULL){
					if(searchList(l, pixelX->right)){
						b4=true;
					}
				}
				B=b1 || b2 || b3 || b4;
				return B;
			}else{
				return true;
			}
		}
	}
}

boolean isPassed(list l, address pixelX){
	if(searchList(l, pixelX)){
		return true;
	}else{
		return false;
	}
}

address search(map m, int X, int Y){
	list l;
	createEmptyList(&l);
	return pixelSearch(&l, m.in, X, Y);
}

address pixelSearch(list *sudahDilewati, address pixel, int x, int y) {
	if(searchList(*sudahDilewati, pixel)){
		return NULL;
	}
	add(sudahDilewati, pixel);
	address pixelDiposisiXY = NULL;
	if(pixel == NULL) {
		return pixelDiposisiXY;
	}
	else if(pixel->position.x == x && pixel->position.y == y) {
		return pixel;
	} else {
			pixelDiposisiXY = pixelSearch(sudahDilewati, pixel->top, x, y);
			if(pixelDiposisiXY == NULL) {
				pixelDiposisiXY = pixelSearch(sudahDilewati, pixel->right, x, y);
			}
			if(pixelDiposisiXY == NULL) {
				pixelDiposisiXY = pixelSearch(sudahDilewati, pixel->bottom, x, y);
			}
			if(pixelDiposisiXY == NULL) {
				pixelDiposisiXY = pixelSearch(sudahDilewati, pixel->left, x, y);
			}
	}
	return pixelDiposisiXY;
}

void addTop(map *m, int Xpredessor, int Ypredessor){
	if(m->in==NULL){
	}else{
		if(Ypredessor == m->width-1){
		}else{
			if(search(*m,Xpredessor, Ypredessor)==NULL){
			}else{
				if(search(*m,Xpredessor, Ypredessor+1)!=NULL){
				}else{
					search(*m,Xpredessor, Ypredessor)->top=createPixel(Xpredessor, Ypredessor+1, NULL, search(*m,Xpredessor, Ypredessor), NULL, NULL);
				}
			}
		}
	}
}

void addBottom(map *m, int Xpredessor, int Ypredessor){
	if(m->in==NULL){
	}else{
		if(Ypredessor == 0){
		}else{
			if(search(*m,Xpredessor, Ypredessor)==NULL){
			}else{
				if(search(*m,Xpredessor, Ypredessor-1)!=NULL){
				}else{
					search(*m,Xpredessor, Ypredessor)->bottom=createPixel(Xpredessor, Ypredessor-1, search(*m,Xpredessor, Ypredessor), NULL, NULL, NULL);
				}
			}
		}
	}
}

void addLeft(map *m, int Xpredessor, int Ypredessor){
	if(m->in==NULL){
	}else{
		if(Xpredessor == 0){
		}else{
			if(search(*m,Xpredessor, Ypredessor)==NULL){
			}else{
				if(search(*m,Xpredessor-1, Ypredessor)!=NULL){
				}else{
					search(*m,Xpredessor, Ypredessor)->left=createPixel(Xpredessor-1, Ypredessor, NULL, NULL, NULL, search(*m,Xpredessor, Ypredessor));
				}
			}
		}
	}
}

void addRight(map *m, int Xpredessor, int Ypredessor){
	if(m->in==NULL){
	}else{
		if(Xpredessor == m->length-1){
		}else{
			if(search(*m,Xpredessor, Ypredessor)==NULL){
			}else{
				if(search(*m,Xpredessor+1, Ypredessor)!=NULL){
				}else{
					search(*m,Xpredessor, Ypredessor)->right=createPixel(Xpredessor+1, Ypredessor, NULL, NULL, search(*m,Xpredessor, Ypredessor), NULL);
				}
			}
		}
	}
}

void showMap(map *m){
	int i,j;
	if(m->in!=NULL){
		for(i=-1;i<m->length;i=i+1){
			for(j=-1;j<m->width;j=j+1){
				if(i==-1 || i==m->length || j==-1 || j==m->width){
					printf(" ");
				}
				if(search(*m, i, j)==NULL){
					printf(" ");
				}else{
					printf("X");
				}
			}
			printf("\n");
		}
	}
}

void deletePixel(map *m, int X, int Y){
	address p;
	p=search(*m, X, Y);
	if(m->in==NULL){
	}else{
		if(m->in->position.x == X && m->in->position.y == Y){
		}else{
			if(p==NULL){
			}else{
				p->top=NULL;
				p->bottom=NULL;
				p->left=NULL;
				p->right=NULL;
				if(search(*m, X-1, Y)!=NULL){
					search(*m, X-1, Y)->right=NULL;
				}
				if(search(*m, X+1, Y)!=NULL){
					search(*m, X+1, Y)->left=NULL;
				}
				if(search(*m, X, Y-1)!=NULL){
					search(*m, X, Y-1)->top=NULL;
				}
				if(search(*m, X, Y+1)!=NULL){
					search(*m, X, Y+1)->bottom=NULL;
				}
				free(p);
			}
		}
	}
}
