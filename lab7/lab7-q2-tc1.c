#include"lab7-q2.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

int main(int argc, char *argv[]){

	FILE *fout;
	DS *S;
	int isCorrect, i;
	
	fout = fopen(argv[1], "w");
	
	/* default, your program is correct */
	isCorrect = 1;
	
	/* check the function, ds_init() */
	S = (DS*)1;
	ds_init(&S, 10);
	
	/* if S is not initialized appropriately */
	if (S == NULL) {
		isCorrect = 0;
	} else if (S->size != 10 || S->parent == NULL) {
		isCorrect = 0;
	} else for (i = 0; i < 10; i++) {
		if (S->parent[i] != i) {
			isCorrect = 0;
		}
	}
	
	
	/* output "Correct" if the ds_init() is correctly implemented */
	if (isCorrect == 1) {
		fprintf(fout, "DS: Correct\n");
	} else {
		fprintf(fout, "DS: Wrong Answer\n");
	}
	fclose(fout);

	return 0;
}

