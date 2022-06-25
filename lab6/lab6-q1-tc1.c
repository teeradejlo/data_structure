#include"lab6-q1.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

int main(int argc, char *argv[]){

	FILE *fout;
	BST *T;
	int isCorrect, i;
	
	fout = fopen(argv[1], "w");
	
	/* default, your program is correct */
	isCorrect = 1;
	
	/* check the function, bst_init() */
	T = (BST*)1;
	bst_init(&T);
	
	/* if T is not initialized appropriately */
	if (T != NULL) {
		isCorrect = 0;
	} 
	
	
	/* output "Correct" if the bst_init() is correctly implemented */
	if (isCorrect == 1) {
		fprintf(fout, "Binary Tree: Correct\n");
	} else {
		fprintf(fout, "Binary Tree: Wrong Answer\n");
	}
	fclose(fout);

	return 0;
}


