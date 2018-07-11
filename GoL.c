#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define TRUE 1
#define FALSE 0
#define SPEED 1000 //duration of one generation.(in micro seconds)

typedef unsigned char bool;

typedef struct _cell_t{
	bool status;
	int count;
	struct _cell_t* adj[8];
}cell_t;

cell_t** init_matrix(int height, int width);
void print_status(cell_t** matrix);
//void print_count(cell_t** matrix);
void set_neighbor(cell_t** matrix);
//void update_neighbor2(cell_t** matrix, int x, int y);
void update_generation(cell_t** matrix);
void birth(cell_t* cell);
void death(cell_t* cell);

int n, m, t;
int gen=0;

int main(int argc, char* argv[]){
	cell_t** cells; //2D array


	/*read options*/
	if( argc < 4 ){
		printf("usage: %s <n> <m> <t>\n",argv[0]);
		return 1;
	}
	n = atoi(argv[1]);
	m = atoi(argv[2]);
	t = atoi(argv[3]);
	system("clear");


	/*initialize*/
	cells = init_matrix(n, m);
	set_neighbor(cells);

	system("clear");
	while( gen <= t ){
		print_status(cells);
		
		update_generation(cells);
		
		usleep(SPEED);
	}


	/*free memory*/
	for( int i =0; i < n; i++)
		free(cells[i]);
	free(cells);

	return 0;
}


cell_t** init_matrix(int height, int width){
	char* input_str = (char*)malloc(sizeof(char)*width);
	
	cell_t** matrix = (cell_t**)malloc(sizeof(cell_t*)*height); 
	for(int i = 0; i < height; i++)	
		matrix[i] = (cell_t*)malloc(sizeof(cell_t)*width);

	/*get matrix from stdin*/
	printf(">> insert %d x %d matrix. (with 1 or 0)\n",n,m);
	for(int i = 0; i < height; i++)
	{
		scanf("%s",input_str);
		for(int j = 0; j < width; j++)
		{
			matrix[i][j].status = (input_str[j] == '1')? TRUE : FALSE;
		}
	}
	free(input_str);
	return matrix;
}

void set_neighbor(cell_t** matrix){
	cell_t* cell;
	for(int y =0; y < n; y++){
		for(int x =0; x < m; x++){
			cell = &matrix[y][x];

			/*check accessability of neighbors*/
			if( y - 1 > 0 && x - 1 > 0){ 
				cell->adj[0] = &matrix[y-1][x-1];
				cell->count += cell->adj[0]->status;
			}
			else cell->adj[0] = NULL;

			if( y - 1 > 0 ){
				cell->adj[1] = &matrix[y-1][x];
				cell->count += cell->adj[1]->status;
			}
			else cell->adj[1] = NULL;

			if( y - 1 > 0 && x + 1 < m){
				cell->adj[2] = &matrix[y-1][x+1];
				cell->count += cell->adj[2]->status;
			}
			else cell->adj[2] = NULL;

			if( x - 1 > 0){
				cell->adj[3] = &matrix[y][x-1];
				cell->count += cell->adj[3]->status;
			}
			else cell->adj[3] = NULL;

			if( x + 1 < m){
				cell->adj[4] = &matrix[y][x+1];
				cell->count += cell->adj[4]->status;
			}
			else cell->adj[4] = NULL;

			if( y + 1 < n && x - 1 > 0){
				cell->adj[5] = &matrix[y+1][x-1];
				cell->count += cell->adj[5]->status;
			}
			else cell->adj[5] = NULL;

			if( y + 1 < n){
				cell->adj[6] = &matrix[y+1][x];
				cell->count += cell->adj[6]->status;
			}
			else cell->adj[6] = NULL;

			if( y + 1 < n && x + 1 < m){
				cell->adj[7] = &matrix[y+1][x+1];
				cell->count += cell->adj[7]->status;
			}
			else cell->adj[7] = NULL;
		}
	}
}


void death(cell_t* cell){
	cell->status = FALSE;
	
	cell_t* neighbor;
	for(int i = 0; i < 8; i++)
	{
		neighbor = cell->adj[i];
		if(neighbor != NULL)
			neighbor->count--;		
	}
}


void birth(cell_t* cell){
	cell->status = TRUE;

	cell_t* neighbor;
	for(int i = 0; i < 8; i++)
	{
		neighbor = cell->adj[i];
		if(neighbor != NULL)
			neighbor->count++;		
	}
}


void update_generation(cell_t** matrix){
	cell_t* cell;
	gen++;

	/*make a copy of count array before modifying it*/ 
	int** tmp = (int**)malloc(sizeof(int*)*n);
	for(int i = 0; i < n; i++){
		tmp[i] = (int*)malloc(sizeof(int)*m);
		for(int j = 0; j < m; j++){
			tmp[i][j] = matrix[i][j].count;
		}
	}
	
	/*find cells to live or die in this generation*/
	for(int i = 0; i < n ; i++){
		for(int j = 0; j < m; j++){
			cell = &matrix[i][j];
			
			if(cell->status == TRUE)
			{
				if(tmp[i][j] != 2 && tmp[i][j] != 3) 
					death(cell);	
			}	
			else if(tmp[i][j] == 3)
			{
				birth(cell);
			}
		}
	}

	for( int i =0; i < n; i++)
		free(tmp[i]);
	free(tmp);
}


void print_status(cell_t** matrix){
	printf("\033[0d\033[0G");//move cursor to (0,0)

	printf("[Generation %d]\n",gen);
	for(int i =0; i < n ; i++){
 		for(int j=0; j < m; j++){
			if(matrix[i][j].status == TRUE)
				printf("[]");
			else
				printf("  ");
		}
		printf("\n");
	}
}

/*
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
*/

/*
void print_count(cell_t** matrix){
	for(int i = 0; i < n; i++){
		for(int j=0; j < m; j++){
			printf("%d ",matrix[i][j].count);
		}
		printf("\n");
	}
}
*/
