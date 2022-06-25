#include"lab8-q2.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

int main(int argc, char *argv[]){

	FILE *fout;
	AdjMatrix *G;
	int isCorrect, i, j;
	
	fout = fopen(argv[1], "w");
	
	/* default, your program is correct */
	isCorrect = 1;
	
	/* check the function, am_graph_init() */
	G = (AdjMatrix*)1;
	am_graph_init(&G, 15);
	
	/* if G is not initialized appropriately */
	if (G == NULL) {
		isCorrect = 0;
	} else if (G->V != 15 || G->E != 0) {
		isCorrect = 0;
	} else {
		for (i = 0; i < 15; i++) for (j = 0; j < 15; j++) {
			if (G->adj[i][j] != 0) {
				isCorrect = 0;
			}
		}
	}
	
	
	/* output "Correct" if the am_graph_init() is correctly implemented */
	if (isCorrect == 1) {
		fprintf(fout, "Graph: Correct\n");
	} else {
		fprintf(fout, "Graph: Wrong Answer\n");
	}
	fclose(fout);

	return 0;
}


