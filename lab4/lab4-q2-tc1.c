#include"lab4-q2.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

int main(int argc, char *argv[]){

	FILE *fout;
	Hash_OA *T;
	int isCorrect, i;

	fout = fopen(argv[1], "w");

	/* default, your program is correct*/
	isCorrect = 1;

	/* check the function, hash_init()*/
	T = NULL;
	hash_init(&T, 11);

	/* if T is not initialized appropriately */
	if (T == NULL) {
		isCorrect = 0;
	} else if (T->size != 11) {
		isCorrect = 0;
	}
	for (i = 0; i < 11; i++) {
		if (T->slots[i].key != HASH_NULL_KEY) isCorrect = 0;
	}
	/* output "Correct" if the hash_init() is correctly implemented*/
	if (isCorrect == 1) {
		fprintf(fout, "Hash: Correct\n");
	} else {
		fprintf(fout, "Hash: Wrong Answer\n");
	}
	fclose(fout);

	return 0;
}

