#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

typedef struct ds {
	int size;		/* size of disjoint set */
	int *parent;	/* parent of each element */
	int *tree_size; /* size of a tree in the disjoint set */
} DS;

/* Your code here */
/* Init a disjoint set with a given size #1 #2 */
/* All node should point to itself */
void ds_init(DS **S, int size){
	/* Your code here */
    DS *tmp = malloc(sizeof(DS));
    tmp->size = size;
    tmp->parent = malloc(sizeof(int) * size);
    tmp->tree_size = malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        tmp->parent[i] = i;
        tmp->tree_size[i] = 1;
    }

    *S = tmp;
}

/* Find the root of node x #3 */
/* Path compression is needed */
/* Return the root of node x */
int ds_find_set(DS *S, int x){
	/* Your code here */
    if (S->parent[x] == x) return x;

	return S->parent[x] = ds_find_set(S, S->parent[x]);
}

/* Check if x and y belong to the same set #4 */
/* Return 1 if they are belong to the same set */
/* Return 0 if they are not belong to the same set */
int ds_same_set(DS* S, int x, int y){
    /* Your code here */
    int rootx = ds_find_set(S, x);
    int rooty = ds_find_set(S, y);

    if (rootx == rooty) {
        return 1;
    } else {
        return 0;
    }
}

/* Union the set containing x and the set containing y #5 #6 */
/* Put the set containing y as the subtree of the set of containing x */
/* You need to update tree_size */
void ds_union(DS *S, int x, int y){
	/* Your code here */
	int rootx = ds_find_set(S, x);
	int rooty = ds_find_set(S, y);

    if (ds_same_set(S, x, y)) {
        return;
    } else {
        S->parent[rooty] = rootx;
        S->tree_size[rootx] += S->tree_size[rooty];
    }
}

/* Union the set containing x and the set containing y #7 #8 */
/* Put the smaller set as the subtree of the larger set */
/* If both sets have the same set, put set containing x as the subtree of set containing y */
/* Remember to update tree_size */
void ds_union_by_size(DS *S, int x, int y){
	/* Your code here */
    int rootx = ds_find_set(S, x);
	int rooty = ds_find_set(S, y);

    if (ds_same_set(S, x, y)) {
        return;
    } else {
        if (S->tree_size[rootx] > S->tree_size[rooty]) {
            S->parent[rooty] = rootx;
            S->tree_size[rootx] += S->tree_size[rooty];
        } else {
            S->parent[rootx] = rooty;
            S->tree_size[rooty] += S->tree_size[rootx];
        }
    }
}

/* Free the disjoint set #9 */
/* Assign NULL pointer to *S */
void ds_free(DS **S){
	/* Your code here */
    if (S == NULL) return;
    if (*S == NULL) return;
    free((*S)->parent);
    free((*S)->tree_size);
    free(*S);
    *S = NULL;
}

int main(int argc, char *argv[]) {

	FILE * fin, * fout;
	DS * S;
	int n, e;
	int i, u, v;
	int ans = 0;

	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	fscanf(fin, "%d%d", &n, &e);
	ds_init(&S, n);

	for (i = 0; i < e; i++) {
		fscanf(fin, "%d%d", &u, &v);
		/* Your code here */
        ds_union(S, u, v);
	}

	/* Your code here */
    int isroot[n];
    memset(&isroot, 0, n * sizeof(int));

    for (i = 0; i < n; i++) {
        int root = ds_find_set(S, i);
        if (isroot[root] == 0) {
            ans++;
            isroot[root] = 1;
        }
    }

	fprintf(fout, "%d\n", ans);

	ds_free(&S);
	fclose(fin);
	fclose(fout);

	return 0;
}


