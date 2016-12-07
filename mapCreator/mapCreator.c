#include "mapCreator.h"

void createEmptyMap(map *m, int lengthX, int widthX){
	m->length=lengthX;
	m->width=widthX;
	m->activePixel=NULL;
	m->in=NULL;
	m->out=NULL;
	printf("\n    Peta kosong telah disiapkan");
	getch();
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
		printf("!!! Pintu masuk telah tersedia sebelumnya\n");
		getch();
	}else{
		if(X > m->length-1 || Y > m->width-1){
			printf("!!! (x) atau (y) yang anda masukkan melebihi batas\n");
			getch();
		}else{
			m->in=createPixel(X, Y, NULL, NULL, NULL, NULL);
			printf("    Pintu masuk telah disiapkan\n");
			getch();
		}
	}
}

void setOut(map *m, address outX){
	if(outX == NULL){
		printf("!!! Pixel yang dimaksud tidak ditemukan dalam peta\n");
		getch();
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
				printf("    pixel-a dan pixel-b berhasil dihubungkan\n");
				getch();
			}else{
				if(a->position.y == b->position.y+1){
					a->bottom=b;
					b->top=a;
					printf("    pixel-a dan pixel-b berhasil dihubungkan\n");
					getch();
				}else{
					printf("!!! pixel-a dan pixel-b tidak berdampingan\n");
					getch();
				}
			}
		}else{
			if(a->position.y == b->position.y){
				if(a->position.x == b->position.x-1){
					a->right=b;
					b->left=a;
					printf("    pixel-a dan pixel-b berhasil dihubungkan\n");
					getch();
				}else{
					if(a->position.x == b->position.x+1){
						a->left=b;
						b->right=a;
						printf("    pixel-a dan pixel-b berhasil dihubungkan\n");
						getch();
					}else{
						printf("!!! pixel-a dan pixel-b tidak berdampingan\n");
						getch();
					}
				}
			}else{
				printf("!!! pixel-a dan pixel-b tidak berdampingan\n");
				getch();
			}
		}
	}else{
		if(a == NULL){
			printf("!!! pixel-a tidak ada\n");
			getch();
		}
		if(b == NULL){
			printf("!!! pixel-b tidak ada\n");
			getch();
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
		printf("!!! Peta masih kosong (tidak terdapat pixel predessor)\n");
		getch();
	}else{
		if(Ypredessor == m->width-1){
			printf("!!! Tidak memungkinkan dilakukan penambahan di atas predessor\n");
			getch();
		}else{
			if(search(*m,Xpredessor, Ypredessor)==NULL){
				printf("!!! Predessor yang dimaksud tidak ada dalam peta\n");
				getch();
			}else{
				if(search(*m,Xpredessor, Ypredessor+1)!=NULL){
					printf("!!! Telah terdapat pixel di atas predessor\n");
					getch();
				}else{
					search(*m,Xpredessor, Ypredessor)->top=createPixel(Xpredessor, Ypredessor+1, NULL, search(*m,Xpredessor, Ypredessor), NULL, NULL);
					printf("    Penambahan berhasil dilakukan\n");
					getch();
				}
			}
		}
	}
}

void addBottom(map *m, int Xpredessor, int Ypredessor){
	if(m->in==NULL){
		printf("!!! Peta masih kosong (tidak terdapat pixel predessor)\n");
		getch();
	}else{
		if(Ypredessor == 0){
			printf("!!! Tidak memungkinkan dilakukan penambahan di atas predessor\n");
			getch();
		}else{
			if(search(*m,Xpredessor, Ypredessor)==NULL){
				printf("!!! Predessor yang dimaksud tidak ada dalam peta\n");
				getch();
			}else{
				if(search(*m,Xpredessor, Ypredessor-1)!=NULL){
					printf("!!! Telah terdapat pixel di bawah predessor\n");
					getch();
				}else{
					search(*m,Xpredessor, Ypredessor)->bottom=createPixel(Xpredessor, Ypredessor-1, search(*m,Xpredessor, Ypredessor), NULL, NULL, NULL);
					printf("    Penambahan berhasil dilakukan\n");
					getch();
				}
			}
		}
	}
}

void addLeft(map *m, int Xpredessor, int Ypredessor){
	if(m->in==NULL){
		printf("!!! Peta masih kosong (tidak terdapat pixel predessor)\n");
		getch();
	}else{
		if(Xpredessor == 0){
			printf("!!! Tidak memungkinkan dilakukan penambahan di samping-kiri predessor\n");
			getch();
		}else{
			if(search(*m,Xpredessor, Ypredessor)==NULL){
				printf("!!! Predessor yang dimaksud tidak ada dalam peta\n");
				getch();
			}else{
				if(search(*m,Xpredessor-1, Ypredessor)!=NULL){
					printf("!!! Telah terdapat pixel di samping-kiri predessor\n");
					getch();
				}else{
					search(*m,Xpredessor, Ypredessor)->left=createPixel(Xpredessor-1, Ypredessor, NULL, NULL, NULL, search(*m,Xpredessor, Ypredessor));
					printf("    Penambahan berhasil dilakukan\n");
					getch();
				}
			}
		}
	}
}

void addRight(map *m, int Xpredessor, int Ypredessor){
	if(m->in==NULL){
		printf("!!! Peta masih kosong (tidak terdapat pixel predessor)\n");
		getch();
	}else{
		if(Xpredessor == m->length-1){
			printf("!!! Tidak memungkinkan dilakukan penambahan di samping-kanan predessor\n");
			getch();
		}else{
			if(search(*m,Xpredessor, Ypredessor)==NULL){
				printf("!!! Predessor yang dimaksud tidak ada dalam peta\n");
				getch();
			}else{
				if(search(*m,Xpredessor+1, Ypredessor)!=NULL){
					printf("!!! Telah terdapat pixel di samping-kanan predessor\n");
					getch();
				}else{
					search(*m,Xpredessor, Ypredessor)->right=createPixel(Xpredessor+1, Ypredessor, NULL, NULL, search(*m,Xpredessor, Ypredessor), NULL);
					printf("    Penambahan berhasil dilakukan\n");
					getch();
				}
			}
		}
	}
}

void showMap(map *m){
	int i,j;
	if(m->in)
	for(i=-1;i<m->length+1;i=i+1){
		for(j=-1;j<m->width+1;j=j+1){
			if(i==-1 || i==m->length){
				printf("|");
			}
			if(j==-1 || j==m->width){
				printf("-");
			}
			if(search(*m, i, j)==NULL){
				printf("X");
			}else{
				printf(" ");
			}
		}
	}
	printf("\n");
}

