#include"lab5-q1.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

int main(int argc, char *argv[]){

	FILE *fout;
	Tree_CS *T;
	int isCorrect, i;
	
	fout = fopen(argv[1], "w");
	
	/* default, your program is correct */
	isCorrect = 1;
	
	/* check the function, tree_init() */
	T = NULL;
	tree_init(&T, 4, 7);
	
	/* if T is not initialized appropriately */
	if (T == NULL) {
		isCorrect = 0;
	} else if (T->key != 4 || T->value != 7 || T->first_child != NULL || T->next_sibling != NULL) {
		isCorrect = 0;
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


