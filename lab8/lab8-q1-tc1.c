#include"lab8-q1.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

int main(int argc, char *argv[]){

	FILE *fout;
	AdjList *G;
	int isCorrect, i;
	
	fout = fopen(argv[1], "w");
	
	/* default, your program is correct */
	isCorrect = 1;
	
	/* check the function, al_graph_init() */
	G = (AdjList*)1;
	al_graph_init(&G, 15);
	
	/* if G is not initialized appropriately */
	if (G == NULL) {
		isCorrect = 0;
	} else if (G->V != 15 || G->E != 0) {
		isCorrect = 0;
	} else {
		for (i = 0; i < 15; i++) {
			if (G->adj[i] != NULL) {
				isCorrect = 0;
			}
		}
	}
	
	
	/* output "Correct" if the al_graph_init() is correctly implemented */
	if (isCorrect == 1) {
		fprintf(fout, "Graph: Correct\n");
	} else {
		fprintf(fout, "Graph: Wrong Answer\n");
	}
	fclose(fout);

	return 0;
}


