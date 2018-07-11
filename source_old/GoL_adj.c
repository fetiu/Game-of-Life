#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#define BIRTH 3
typedef unsigned char bool;

typedef struct _cell_t{
	bool status;
	int count;
	cell_t* adj[8];
}cell_t;

cell_t** init_matrix(int n, int m);
void print_matrix(cell_t** cells, int n, int m);

int count_neighbor(cell_t* cell);
void update_neighbor(cell_t* cell);
void update_status(cell_t* cell);


int main(int argc, char* argv[]){
	cell_t** cells;
	int n, m, t;
	int seq=0;
	int fd;

	if( argc < 4 ){
		printf("usage: %s <n> <m> <t>\n",argv[0]);
		return 1;
	}
	n = atoi(argv[1]);
	m = atoi(argv[2]);
	t = atoi(argv[3]);

	cell = init_matrix(fd, n, m);

	while( seq < t ){
		printf("[Sequence %d]\n", seq);
		print_matrix(cells, n, m);

// 		for(int i=0; i < n; i++){
// 			for(int j=0; j < m; j++){
// 				count_neighbor(cell[i][j]);
// 			}
// 		}//checking whole element is inefficient. thread might solve it?
//
		
		seq++;
		usleep(500);
	}

	system("clear");
	for( int i =0; i < n; i++)
		free(cell[i]);
	free(cell);
	return 0;
}


cell_t** init_matrix(int n, int m){
	cell_t** matrix;
	char* input = (char*)malloc(sizeof(char)*(m+1));//include \n

	matrix = (cell_t**)malloc(sizeof(cell_t*)*n);
	for(int i = 0; i < n; i++){
		matrix[i] = (int*)malloc(sizeof(cell_t)*m);
	}
	//random initalize.
	printf(">> insert %d x %d matrix. (with 1 or 0)\n",n,m);
	
	for(int i = 0; i < n; i++){
		fgets(input, sizeof(input), stdin);
		printf("\n");
		for(int j = 0; j < m; j++){
			matrix[i][j].status = (bool)atoi(input[j]);

			//set_adjacency
			for(int a =0; a < 8; a++){
				if(i > 0 && i < n && j > 0 && j < m)
					adj[a] = &matrix[i][j];
				else
					adj[a] = NULL;
			}
		}
	}
	free(input);
	return matrix;
}

int count_neighbor(cell_t* cell){
	for(int a =0; a < 8; a++)


	
			if( matrix[i][j].status == true ){
				matrix[i][j].count = BIRTH;//3
				check_neighbor(
				//this time also apply?
			}
			else
				matrix[i][j].count = 0;
	return cnt;
}

void update_neighbor(cell_t* cell){
	int val = (cell.status == true)? 1:-1;

	for(int i = 0; i < 8; i++){
			cell.adj[i]->count += val;

}

void update_status(cell_t* cell){
	
}


void print_matrix(cell_t** cell, int n, int m){
	printf("\033[1d\033[0G");//move cursor to (0,1)

	for(int i =0; i < n ; i++){
 		for(int j=0; j < m; j++){
			if(cell[i][j].status == true)
				printf("#");
			else
				printf(" ");
		}
		printf("\n");
	}
	printf("\n");
}
