#include"lab7-q1.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

int main(int argc, char *argv[]){

	FILE *fout;
	MaxHeap *H;
	int isCorrect, i;
	
	fout = fopen(argv[1], "w");
	
	/* default, your program is correct */
	isCorrect = 1;
	
	/* check the function, maxheap_init() */
	H = (MaxHeap*)1;
	maxheap_init(&H, 15);
	
	/* if H is not initialized appropriately */
	if (H == NULL) {
		isCorrect = 0;
	} else if (H->maxsize != 15 || H->count != 0 || H->data == NULL) {
		isCorrect = 0;
	}
	
	
	/* output "Correct" if the maxheap_init() is correctly implemented */
	if (isCorrect == 1) {
		fprintf(fout, "Heap: Correct\n");
	} else {
		fprintf(fout, "Heap: Wrong Answer\n");
	}
	fclose(fout);

	return 0;
}

