#include"lab7-q2.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

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


