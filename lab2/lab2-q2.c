#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>

/* return 0 for same */
/* return negative for A < B */
/* return positive for A > B */
/* pay attension to alphebatical order! */
int compare(char *A, char *B) {
	/* Your code here */
	int i = 0;
	//while string not end
	while(A[i] != 0 && B[i] != 0) {
        //if ascii not the same
        if (A[i] != B[i]) {
            if (tolower(A[i]) == tolower(B[i])) {
                //same letter but different upper/lower
                if (A[i] > B[i]) {
                    //A is upper, B is lower
                    return 1;
                } else {
                    //A is lower, B is upper
                    return -1;
                }
            } else {
                //letter not the same
                return tolower(A[i]) - tolower(B[i]);
            }
        }
        i++;
	}
	if (A[i] == 0 && B[i] != 0) {
        return -1;
	}
	if (A[i] != 0 && B[i] == 0) {
        return 1;
	}

	return 0;
}

/* Insersion sort algorithm */
void insertionsort(int n, char ** a, FILE *fout){
    int i, j;
	char *tmpptr;

	for (i = 1; i < n; i++) {
		/* Your code here */
        tmpptr = a[i];

        for (j = i; j > 0 && compare(a[j-1], tmpptr) > 0; j--) {
            a[j] = a[j-1];
        }
        a[j] = tmpptr;

        /* Output format */;
		for (j = 0; j < n-1; j++)
			fprintf(fout, "%s ", a[j]);
		fprintf(fout, "%s\n", a[n-1]);

	}
}

/* You don't need to change the main */
int main(int argc, char *argv[]) {

	FILE *fin, *fout;
	int n;
	char **data;
	int i;

	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	fscanf(fin, "%d", &n);
	data = (char**) malloc(sizeof(char*)*n);
	printf("n = %d\n", n);
	for (i = 0; i < n; i++) {
		data[i] = (char*)malloc(sizeof(char)*100);
		memset(data[i], 0, sizeof(char)*100);
		fscanf(fin, "%s", data[i]);
	}

	for (i = 0; i < n-1; i++)
		printf("%s ", data[i]);
	printf("%s\n", data[n-1]);

	insertionsort(n, data, fout);

	for (i = 0; i < n; i++) {
		free(data[i]);
	}
	free(data);


	fclose(fin);
	fclose(fout);

	return 0;
}


