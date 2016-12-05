#include "mapCreator.h"

void createPixel(map *m, int rowX, int columnX, address topX, address bottomX, address leftX, address rightX){
	*m=(address)malloc(sizeof(pixel));
	if(*m!=NULL){
		(*(*(*m)).position).row=rowX;
		(*(*(*m)).position).column=columnX;
		(*(*m)).passable=FALSE;
		(*(*m)).top=topX
		(*(*m)).bottom=bottomX
		(*(*m)).left=leftX
		(*(*m)).right=rightX;
	}
}

address searchPixel(map m, int rowX, int columnX, int length, int width){
	if(m==NULL || rowX>=width || columnX>=length){
		return NULL;
	}
	else{
		if((*(*m).position).row==rowX && (*(*m).position).column==columnX){
			return m;
		}
		else{
			if((*(*m).position).row<rowX){
				searchPixel((*m).bottom, rowX, columnX, length, width);
			}
			else{
				if((*(*m).position).column<columnX){
					searchPixel((*m).right, rowX, columnX, length, width);
				}
			}
		}
	}
}

void createMap(map ltc, map *m, int rowX, int columnX, int length, int width){
	if(*m==NULL){
		createPixel(&*m, rowX, columnX, TRUE, searchPixel(*m, rowX-1, columnX, length, width), searchPixel(*m, rowX+1, columnX, length, width), searchPixel(*m, rowX, columnX-1, length, width), searchPixel(*m, rowX, columnX+1, length, width));
		if(rowX<width){
			createMap(ltc, &(*(*m)).bottom, rowX+1, columnX, length, width);
		}
		else{
			if(columnX<length){
				createMap(ltc, &searchPixel(ltc, 0, columnX+1, length, width), 0, columnX+1, length, width);
			}
		}
	}
}

void createObstacle(map *m, int rowLTC, int columnLTC, int length, int width){
	int currentRow;
	int currentColumn;
	if(*m!=NULL){
		for(currentRow=rowLTC; currentRow<rowLTC+width; currentRow=currentRow+1){
			for(currentColumn=columnLTC; currentColumn<columnLTC+length; currentColumn=currentColumn+1){
				(*searchPixel(*m, currentRow, currentColumn, length, width)).passable=TRUE;
			}
		}
	}
}