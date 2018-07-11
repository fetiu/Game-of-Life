#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#define BIRTH 3
typedef unsigned char bool;

struct cell_t{
	bool status;
	int count;
	int* adj[8];
}

int** init_matrix(int n, int m);
void print_matrix(int**cell, int n, int m);
int check_neighbor();
int update_generation();


int main(int argc, char* argv[]){
	int	**cell;
	int n, m, t;
	int seq=0;

	if( argc < 4 ){
		printf("usage: %s <n> <m> <t>\n",argv[0]);
		return 1;
	}
	n = atoi(argv[1]);
	m = atoi(argv[2]);
	t = atoi(argv[3]);

	cell = init_matrix(n, m);

	while( seq < t ){
		print_matrix(cell, n, m);

// 		for(int i=0; i < n; i++){
// 			for(int j=0; j < m; j++){
// 				cell[i][j]i = check_neighbor(i,j);
// 			}
// 		}//checking whole element is inefficient. thread might solve it?
//
		
		seq++;
	}

	system("clear");
	for( int i =0; i < n; i++)
		free(cell[i]);
	free(cell);
	return 0;
}


int** init_matrix(int n, int m){
	int**matrix;

	int array[5][5] = 
	{
		{1,2,1,0,0},
		{1,1,1,0,0},
		{0,1,0,0,0},
		{1,2,2,0,0},
		{0,3,0,0,0},
	};

	matrix = (int**)malloc(sizeof(int*)*n);
	for( int i =0; i < n; i++){
		matrix[i] = (int*)malloc(sizeof(int)*m);
		memset(matrix[i],2, sizeof(int)*m );
	}
	
	//random.
	return matrix;
}

//int check 


void print_matrix(int**cell, int n, int m){
	printf("\033[0d\033[0G");

	for(int i =0; i < n ; i++){
 		for(int j=0; j < m; j++){
			if(cell[i][j] == BIRTH)
				printf("B");
			else if( cell[i][j] == SURVIVE)
				printf("S");
			else
				printf(" ");
		}
		printf("\n");
	}
	printf("\n");
}
