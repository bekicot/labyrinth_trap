#include "mapCreator.h"

int main(){
	
	map m;
	
	//createEmptyMap
	int lengthX, widthX;
	printf("MEMPERSIAPKAN PETA KOSONG\n\n");
	printf("Masukkan panjang peta yang diinginkan : ");
	scanf("%i",&lengthX);
	printf("\nMasukkan lebar peta yang diinginkan : ");
	scanf("%i",&widthX);
	createEmptyMap(&m, lengthX, widthX);
	system("cls");
	printf("\nPeta kosong telah disiapkan");
	getch();
	system("cls");
	//createEmptyMap
	
	//creteIn
	int X, Y;
	printf("Masukkan koordinat (x) untuk pintu masuk : ");
	scanf("%i",&X);
	printf("\nMasukkan koordinat (y) untuk pintu masuk : ");
	scanf("%i",&Y);
	createIn(&m, X, Y);
	getch();
	system("cls");
	//createIn
	
	//search
	/*
	if(search(m.in,13,9)==NULL){
		printf("tidak ketemu");
	}else{
		printf("ketemu, dengan koordinat (%i,%i)",search(m.in,13,9)->position.x,search(m.in,13,9)->position.y);
	}
	*/
	//search
	
	addTop(&m, 0, 0);
	if(search(m.in,0,2)==NULL){
		printf("tidak ketemu");
	}else{
		printf("ketemu, dengan koordinat (%i,%i)",search(m.in,0,2)->position.x,search(m.in,0,2)->position.y);
	}
	return 0;
}
