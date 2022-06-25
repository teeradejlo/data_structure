#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>

/* return 0 for same */
/* return negative for A < B */
/* return positive for A > B */
/* pay attension to lexicographical order! */
int compare(char *A, char *B) {
	/* Your code here */
	return strcmp(A, B);
}

/* swap a[x] with a[y] */
void swap(char **a, int x, int y) {
    /* Your code here */
    char* tmp = a[x];
    a[x] = a[y];
    a[y] = tmp;
}

/* after median3 */
/* a[l] is the pivot */
/* a[r] > a[c] */
int median3(char** a, int l, int r){
    int c = (l + r) / 2;
    /* Your code here */
    if (compare(a[l], a[c]) > 0) {
        swap(a, l, c);
    }
    if (compare(a[l], a[r]) > 0) {
        swap(a, l, r);
    }
    if (compare(a[c], a[r]) > 0) {
        swap(a, c, r);
    }
    swap(a, l, c);

    return l;
}

/* Quicksort algorithm */
void my_qsort(char**a, int left, int right, int n, FILE *fout){
    int k;
    int i, j, p;
    /* Your code here */
    if (left>=right) return;

    if (left+1 == right) {
        if (compare(a[left], a[right]) > 0) {
            swap(a, left, right);
        }
        return;
    }

    p = median3(a, left, right); //left
    i = left+1;
    j = right;

    while (1) {
        while (compare(a[i], a[p]) <= 0 && i <= right) {
            i++;
        }
        while (compare(a[j], a[p]) >= 0 && j >= left) {
            j--;
        }
        if (i < j) {
            swap(a, i, j);
        } else {
            break;
        }
    }
    swap(a, i-1, p);

	/* Output format */
	for (k = 0; k < n-1; k++)
		fprintf(fout, "%s ", a[k]);
	fprintf(fout, "%s\n", a[n-1]);

	/* Your code here */
	/* change 0 to some variables, formulae */
    my_qsort(a, left, i-2, n, fout);
    my_qsort(a, i, right, n, fout);
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

	my_qsort(data, 0, n-1, n, fout);

	for (i = 0; i < n; i++) {
		fprintf(fout, "%s", data[i]);
		if (i != n-1) fprintf(fout, " ");
		else fprintf(fout, "\n");
		free(data[i]);
	}
	free(data);


	fclose(fin);
	fclose(fout);

	return 0;
}


