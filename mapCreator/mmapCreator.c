#include "mapCreator.h"

int main(){
	
	map m; // map berukuran (0,0) hingga (+x,+y)
	
	//createEmptyMap
	int lengthX, widthX;
	printf("MEMPERSIAPKAN PETA KOSONG\n\n");
	printf("Masukkan panjang peta yang diinginkan : ");
	scanf("%i",&lengthX);
	printf("\nMasukkan lebar peta yang diinginkan : ");
	scanf("%i",&widthX);
	createEmptyMap(&m, lengthX, widthX);
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
	
	//manually create map
	boolean stop=false;
	int option; 
	while(stop==false){
		printf("Masukkan koordinat (x) predessor : ");
		scanf("%i",&X);
		printf("\nMasukkan koordinat (y) predessor : ");
		scanf("%i",&Y);
		printf("\nMasukkan lokasi penambahan pixel (atas=1, bawah=2, kiri=3, kanan=4) : ");
		scanf("%i",&option);
		switch(option){
			case 1 : addTop(&m, X, Y);break;
			case 2 : addBottom(&m, X, Y);break;
			case 3 : addLeft(&m, X, Y);break;
			case 4 : addRight(&m, X, Y);break;
			default : printf("\n!!! opsi yang anda masukkan tidak berada dalam range-nya");break;
		}
		printf("\nApakah anda ingin menambah pixel lagi ? (y=1, n=0) : ");
		scanf("%i",&option);
		if(option==1){
			stop=false;
		}else{
			stop=true;
		}
		getch();
		system("cls");
	}
	if(search(m, 1, 0)!=NULL){
		printf("(%i,%i)",search(m, 1, 0)->position.x,search(m, 1, 0)->position.y);
		getchar();
	}
	//manually create map
	
	//manually connect pixel
	int xa,xb,ya,yb;
	stop=false;
	while(stop==false){
		printf("Masukkan koordinat (x) pixel-a : ");
		scanf("%i",&xa);
		printf("\nMasukkan koordinat (y) pixel-a : ");
		scanf("%i",&ya);
		printf("\nMasukkan koordinat (x) pixel-b : ");
		scanf("%i",&xb);
		printf("\nMasukkan koordinat (y) pixel-b : ");
		scanf("%i",&yb);
		connect(search(m, xa, ya), search(m, xb, yb));
		printf("\nApakah anda ingin menghubungkan pixel lagi ? (y=1, n=0) : ");
		scanf("%i",&option);
		if(option==1){
			stop=false;
		}else{
			stop=true;
		}
		getch();
		system("cls");
	}
	//manually connect pixel
	
	//setOut
	printf("Masukkan koordinat (x) pixel pintu keluar : ");
	scanf("%i",&X);
	printf("\nMasukkan koordinat (y) pixel pintu keluar : ");
	scanf("%i",&Y);
	setOut(&m, search(m, X, Y));
	getch();
	system("cls");
	//setOut
	
	//show map
	printf("Tampilan peta\n");
	showMap(&m);
	//show map
	
	return 0;
}
