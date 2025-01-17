#include<stdio.h>
#include<stdlib.h>

int ** board;
int** createBoard(int,int,int);  
void printBoard(int);
void trominoTile(int);
int trominoTileRec(int,int,int);
int cnt=0;
void putTromino(int,int,int,int,int,int);
void freeMemory(int);
/*
* Main function where the execution starts.
*/
int main(int argc,char ** argv) {
	int i,k,hr,hc,size=1;
	if(argc!=4) {
		printf("Error: Invalid number of arguments!\n");
		return 0;
	}

	k=atoi(argv[1]);
	hr=atoi(argv[2]);
	hc=atoi(argv[3]);
	for(i=0;i<k;i++){
		size = 2*size;
	}
	board = createBoard(size,hr,hc);
	printBoard(size);
	trominoTile(size);
	printf("\n\n");
	printBoard(size);
	
	freeMemory(size);	
	return 0;
}

/*
* Wrapper class which calls trominoTileRec 
*/
void trominoTile(int size) {
  	trominoTileRec(size,0,0);
}

/*
* TrominoTile Recursive function
*/
int trominoTileRec(int n,int x,int y) {
	int i,j,hr,hc;	
	if(n == 2){
		cnt++;
		for(i=0;i<n;i++) {
			for(j=0;j<n;j++){
				if(board[x+i][y+j]==0)
					board[x+i][y+j]=cnt;
			}
		}
		return 0;
	}
	//Search the hole's location
	for(i=x;i<x+n;i++) {
		for(j=y;j<y+n;j++){
			if(board[i][j] != 0) {
				hr=i; hc=j;
			}
		}
	}
    //printf("n = %d, hole at (%d, %d) with (%d, %d)\n", n,hr, hc, x, y);
	//If missing Tile is in 1st quadrant
	if(hr< x + n/2 &&hc < y+ n/2) {
		putTromino(x+n/2,y+ (n/2) - 1,x+n/2,y+n/2,x+n/2-1,y+n/2);		
	}
	//If missing Tile is in 2st quadrant
	else if(hr>=x+ n/2 && hc < y + n/2) {
		putTromino(x+n/2-1,y+ (n/2),x+n/2,y+n/2,x+n/2-1,y+n/2-1);		
	}
	//If missing Tile is in 3st quadrant
	else if(hr < x + n/2 && hc >= y + n/2) {
		putTromino(x+(n/2),y+ (n/2)-1,x+(n/2),y+n/2,x+(n/2)-1,y+(n/2) -1);		
	}
	//If missing Tile is in 4st quadrant
	else if(hr >= x + n/2 && hc >= y + n/2) {
		putTromino(x+(n/2) -1, y+ (n/2),x+(n/2),y+(n/2) -1,x+(n/2)-1,y+(n/2)-1);		
	}
	trominoTileRec(n/2, x, y+n/2);
	trominoTileRec(n/2, x, y);
	trominoTileRec(n/2, x+n/2, y);
	trominoTileRec(n/2, x+n/2, y+n/2);
	
	return 0;

}

void putTromino(int x1,int y1,int x2,int y2,int x3, int y3) {
	cnt++;
	//printf(" %d, (%d, %d), (%d, %d), (%d, %d) \n", cnt, x1, y1, x2, y2, x3, y3); 
	board[x1][y1] = cnt;
	board[x2][y2] = cnt;
	board[x3][y3] = cnt;
}
/*
* Create the Borad and initialize all except hole to zero
*/
int ** createBoard(int n,int hr,int hc){
	int ** array = (int**)malloc(n*sizeof(int *));	
	int i,j;
	for(i = 0;i < n; i++) {
	    	array[i] = (int*)malloc(n*sizeof(int));
   	 	for(j = 0; j < n; j++) {
			if((i==hr) && (j==hc))
				array[i][j]=-1;
			else
	        		array[i][j] = 0;
	    	}
	}
	return array;
}

/*
* Prints the Board
*/
void printBoard(int n){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++) {
			printf(" %3d ",board[i][j]);
		}
		printf("\n");
	}
}

void freeMemory(int n){	
	int i;
	for(i=0;i<n;i++)
		free(board[i]);
	free(board);
}
