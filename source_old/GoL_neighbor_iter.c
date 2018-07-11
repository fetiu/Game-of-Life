#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
#define SPEED 5000
typedef unsigned char bool;

typedef struct _cell_t{
	bool status;
	int count;
	struct _cell_t* adj[8];
}cell_t;

int n, m, t;
int gen=0;

cell_t** init_matrix(int height, int width);
void print_status(cell_t** matrix);
void print_count(cell_t** matrix);

void set_neighbor(int y, int x, cell_t** matrix);

void update_generation(cell_t** matrix);
void update_neighbor(cell_t* cell);
void update_neighbor2(cell_t** matrix, int x, int y);

int main(int argc, char* argv[]){
	cell_t** cells; //2D array

	//read options
	if( argc < 4 ){
		printf("usage: %s <n> <m> <t>\n",argv[0]);
		return 1;
	}
	n = atoi(argv[1]);
	m = atoi(argv[2]);
	t = atoi(argv[3]);
	system("clear");
	
	//initialize
	cells = init_matrix(n, m);

	while( gen < t ){
		print_status(cells);
		
		update_generation(cells);
		
		//print_count(cells);
	
		gen++;
		sleep(1);
		//usleep(SPEED);
	}

	for( int i =0; i < n; i++){
		free(cells[i]);
	}
	free(cells);

	return 0;
}


cell_t** init_matrix(int height, int width){
	char* input_str = (char*)malloc(sizeof(char)*width);
	cell_t** matrix = (cell_t**)malloc(sizeof(cell_t*)*height); 
	for(int i = 0; i < height; i++)	
		matrix[i] = (cell_t*)malloc(sizeof(cell_t)*width);
		
	puts("malloc1\n");
	//get matrix from stdin
	printf(">> insert %d x %d matrix. (with 1 or 0)\n",n,m);
	
	for(int i = 0; i < height; i++)
	{
		scanf("%s",input_str);
		for(int j = 0; j < width; j++)
		{
			matrix[i][j].status = (input_str[j] == '1')?TRUE:FALSE;
		}
	}
	print_status(matrix);
	
	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++)
			set_neighbor(i, j, matrix);

	print_status(matrix);
	free(input_str);
	return matrix;
}


void set_neighbor(int y, int x, cell_t** matrix){
	int next=0;
	cell_t* cell = &matrix[y][x];
	cell->count = 0;

	printf("counting cell %d",cell->status);
	for(int i = y-1; i <= y+1; i++){
		for(int j = x-1; j <= x+1; j++){
			if( i != y || j != x){
				next++;
				if(i>-1 && i<n && j>-1 && j<m){
					cell->count += matrix[i][j].status;
					cell->adj[next] = &matrix[i][j];//save address of neighbor
				}
				else
					cell->adj[next] = NULL;
			}
		}
	}
	printf("counted cell %d\n", cell->count);
	//printf("%d\n",next);
}



void update_neighbor(cell_t* cell){
	int val = (cell->status == TRUE)? 1:-1;
	cell_t* neighbor;

	for(int i = 0; i < 8; i++){
		neighbor = cell->adj[i];
		if(neighbor != NULL)
			neighbor->count += val;		
	}
}



void update_neighbor2(cell_t** matrix, int x, int y){
	int val = (matrix[y][x].status == TRUE)? 1:-1;

	for(int i = y-1; i <= y+1; i++){
		for(int j = x-1; j <= x+1; j++){
			if(i>-1 && i<n && j>-1 && j<m)
				if( i != y || j != x)
					matrix[i][j].count += val;
		}
	}
}


void update_generation(cell_t** matrix){
	cell_t* cell;

	//to update count later, make a copy of count array.
	int** tmp = (int**)malloc(sizeof(int*)*n);
	for(int i = 0; i < n; i++){
		tmp[i] = (int*)malloc(sizeof(int)*m);
		for(int j = 0; j < m; j++)
			tmp[i][j] = matrix[i][j].count;
	}

	for(int i = 0; i < n ; i++){
		for(int j = 0; j < m; j++){
			cell = &matrix[i][j];
			if( cell->status == TRUE){
				if(tmp[i][j] < 2 || tmp[i][j] > 3){//Death
					cell->status = FALSE;
					update_neighbor(cell);//neighbor
				}
			}
			else //FALSE
				if(tmp[i][j] == 3){ //Birth
					cell->status = TRUE;
					update_neighbor(cell);
				}
		}
	}

	for( int i =0; i < n; i++)
		free(tmp[i]);
	free(tmp);
}

void print_status(cell_t** matrix){
	//printf("\033[2d\033[0G");//move cursor to (0,1)

	printf("[Generation %d]",gen);
	for(int i =0; i < n ; i++){
 		for(int j=0; j < m; j++){
			if(matrix[i][j].status == TRUE)
				printf("[]");
			else
				printf("  ");
		}
		printf("\n");
	}
	printf("\n");
}

void print_count(cell_t** matrix){
	for(int i = 0; i < n; i++){
		for(int j=0; j < m; j++){
			printf("%d ",matrix[i][j].count);
		}
		printf("\n");
	}
}

