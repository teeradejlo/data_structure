#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

/* conquer step in merge sort */
void merge(int a[], int tmpa[], int l, int r, int rend, int maxlen, FILE *fout){
    int i, t = l, lend = r - 1, n = rend - l + 1;
	/* Your code here */
	if (n<=1) return;

    //main loop
    while (l <= lend && r <= rend) {
        if (a[l] >= a[r]) tmpa[t++] = a[l++];
        else tmpa[t++] = a[r++];
    }

    //copy the remaining
    while (l <= lend) {
        tmpa[t++] = a[l++];
    }
    while (r <=rend) {
        tmpa[t++] = a[r++];
    }

    //copy tmpa back to a[]
    //i = 0; i < n; i++, rend--
    for (i = rend; i >= 0; i--) {
        a[i] = tmpa[i];
    }


	/* Output format */;
	for (i = 0; i < maxlen-1; i++)
		fprintf(fout, "%d ", a[i]);
	fprintf(fout, "%d\n", a[maxlen-1]);
}

/* divide step in merge sort */
void msort(int a[], int tmpa[], int left, int right, int maxlen, FILE *fout){
    int center;
    if (left < right){
        center = (left + right) / 2;

        /* Your code here */
        /* change 0 to some variables, formulae */
        msort(a, tmpa, left, center, maxlen, fout);
        msort(a, tmpa, center + 1, right, maxlen, fout);
        merge(a, tmpa, left, center+1, right, maxlen, fout);
    }
}

/* preparation for merge sort */
/* You don't need to change this function */
void mergesort(int n, int a[], FILE *fout){     /* driver */
    int *tmpa = (int *)malloc(n * sizeof(int)); /* memory for merged list */

    msort(a, tmpa, 0, n - 1, n, fout);
    free(tmpa);
}

/* You don't need to change the main */
int main(int argc, char *argv[]) {

	FILE *fin, *fout;
	int n;
	int *data;
	int i;

	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	fscanf(fin, "%d", &n);
	data = (int*) malloc(sizeof(int)*n);
	for (i = 0; i < n; i++) fscanf(fin, "%d", data+i);

	mergesort(n, data, fout);

	free(data);


	fclose(fin);
	fclose(fout);

	return 0;
}


