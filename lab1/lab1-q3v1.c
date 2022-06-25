#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

/* You can implement some functions */
/* You may edit and reuse some code in lab1-q1 or lab1-q2 */
/* We only accept a single c file, no multiple files for 1 question */


int main(int argc, char *argv[]) {

	FILE *fin, *fout;
	int n , k ;

	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");
	fscanf(fin, "%d%d", &n, &k);

	/* Your code here */
	int* numberArr = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
        numberArr[i] = i+1;
	}

	int delIndex = 0;
    int lapcount = 0;

	for (int i = 0; i < n; i++) {
        while (lapcount < k - 1) {
            if (numberArr[delIndex] > 0) {
                lapcount++;
            }
            delIndex = (delIndex + 1) % n;
        }

        if (i > 0) {
            while(numberArr[delIndex] < 0) {
                delIndex = (delIndex + 1) % n;
            }
        }

        lapcount = 0;
        fprintf(fout, "%d", numberArr[delIndex]);
        numberArr[delIndex] = -1;
        if (i < n-1) {
            while (numberArr[delIndex] < 0) {
                delIndex = (delIndex + 1) % n;
            }
            fprintf(fout, " ");
        }
	}
	fprintf(fout, "\n");

	fclose(fin);
	fclose(fout);

	return 0;
}


