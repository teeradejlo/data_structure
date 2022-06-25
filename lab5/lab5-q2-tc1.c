#include"lab5-q2.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<math.h>

int main(int argc, char *argv[]){

	FILE *fout;
	BTree *T;
	int isCorrect, i;	
	fout = fopen(argv[1], "w");
	
	/* default, your program is correct */
	isCorrect = 1;
	
	/* check the function, tree_init() */
	T = NULL;
	tree_init(&T, 4, 7.0, 10);
	
	/* if T is not initialized appropriately */
	if (T == NULL) {
		isCorrect = 0;
	} else if (T->max_size != 10) {
		isCorrect = 0;
	} else if (T->key[0] != 4 || fabs(T->value[0] - 7) > 1e-8) {
		isCorrect = 0;
	} else {
		for (i = 1; i < 10; i++) {
			if (T->key[i] != INT_MAX || fabs(T->value[i] + 2100) > 1e-8) {
				isCorrect = 0;
			}
		}
	}
	
	/* output "Correct" if the tree_init() is correctly implemented */
	if (isCorrect == 1) {
		fprintf(fout, "Tree: Correct\n");
	} else {
		fprintf(fout, "Tree: Wrong Answer\n");
	}
	fclose(fout);

	return 0;
}

