#include"lab8-q3.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

int main(int argc, char *argv[]){

	FILE *fout;
	EdgeList *G;
	int isCorrect, i, j;

	fout = fopen(argv[1], "w");

	/* default, your program is correct */
	isCorrect = 1;

	/* check the function, el_graph_init() */
	G = (EdgeList*)1;
	el_graph_init(&G, 15, 30);

	/* if G is not initialized appropriately */
	if (G == NULL) {
		isCorrect = 0;
	} else if (G->V != 15 || G->E != 0 || G->Emax != 30) {
		isCorrect = 0;
	} else {
		for (i = 0; i < 15; i++) {
			if (G->edgelist[i].v != 0 || G->edgelist[i].w != 0 || G->edgelist[i].weight != 0) {
				isCorrect = 0;
			}
		}
	}

	/* output "Correct" if the el_graph_init() is correctly implemented */
	if (isCorrect == 1) {
		fprintf(fout, "Graph: Correct\n");
	} else {
		fprintf(fout, "Graph: Wrong Answer\n");
	}
	fclose(fout);

	return 0;
}


