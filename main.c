#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#include "life.h"

#define SECONDS_US 1000000
#define DELAY 0.1 * SECONDS_US //duration of one generation.

char* input_matrix(int width, int height);

int main(int argc, char* argv[]){
	int w, h, t;

	/*read options*/
	if( argc < 4 ){
		printf("usage: %s <w> <h> <t>\n",argv[0]);
		return 1;
	}
	w = atoi(argv[1]);
	h = atoi(argv[2]);
	t = atoi(argv[3]);
	system("clear");

	/* initialize */
	char* world = input_matrix(w, h);

	struct life_s* life = life_begin(world, w, h);

	for(int i = 0; i <= t; i++)
	{
		life_draw(life);

		/* show time elapsed below */
		printf("\033[%ddt: %d\n", h + 2, i);

		usleep(DELAY);
		life_update(life);
	}

	/* free memory */
	life_end(life);
	free(world);
	return 0;
}

char *input_matrix(int width, int height)
{
	char *matrix = calloc(width * height + 1, sizeof(char)); // +1 for null
	char *line = NULL;
	size_t size;

	/* get matrix from stdin */
	printf(">> insert %d x %d matrix (o: alive, else: empty)\n", width, height);

	while (strlen(matrix) < width * height)
	{
		int n = getline(&line, &size, stdin) - 1; // to not count line feed
		if (n > width)
		{
			printf("\033[1A\033[K"); // go up and erase line
			continue;
		}
		/* Fill the rest with null */
		memset(line + n, 0, width - n);
		printf("\033[1A%s|\n", line); // show priview of line
		strncat(matrix, line, width);
	}
	free(line);
	return matrix;
}
