#include"lab5-q2.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<math.h>

/* Initialize the tree with a root #1 */
/* Create a empty BTree first */
/* The root (key, value) is stored at (key[0], value[0]) */
/* If key is unused, set key = INT_MAX, value = -2100 */
void tree_init(BTree **T, int key, double value, int max_size){
	/* Your code here */
	BTree *tmp = malloc(sizeof(BTree));

	tmp->max_size = max_size;
	tmp->key = malloc(sizeof(int) * max_size);
	tmp->value = malloc(sizeof(double) * max_size);

	int i = 0;
	for (i = 0; i < max_size; i++) {
        tmp->key[i] = INT_MAX;
        tmp->value[i] = -2100;
	}
	tmp->key[0] = key;
	tmp->value[0] = value;

	*T = tmp;
}

/* Initialize the tree with arrays #2 */
/* Create a empty BTree first */
/* n defines the number of (key,value) pairs of the array */
/* If key is unused, set key = INT_MAX, value = -2100 */
void tree_init_with_array(BTree **T, int *key, double *value, int n, int max_size){
	/* Your code here */
    BTree *tmp = malloc(sizeof(BTree));

	tmp->max_size = max_size;
	tmp->key = malloc(sizeof(int) * max_size);
	tmp->value = malloc(sizeof(double) * max_size);

	int i = 0;
	for (i = 0; i < n; i++) {
        tmp->key[i] = key[i];
        tmp->value[i] = value[i];
	}
	for (i = n; i < max_size; i++) {
        tmp->key[i] = INT_MAX;
        tmp->value[i] = -2100;
	}
	*T = tmp;
}

/* Initialize the empty tree with height of root #3 */
/* Based on the height, calculate the max_size */
/* Create a empty BTree with max_size */
/* If key is unused, set key = INT_MAX, value = -2100 */
void tree_init_with_height(BTree **T, int height){
	/* Your code here */
	int max_size = 0;
	int add_factor = 1;
	int i;
	for (i = 0; i <= height; i++) {
        max_size += add_factor;
        add_factor *= 2;
	}

    tree_init(T, INT_MAX, -2100, max_size);
}

/* Get the index of parent #4 */
/* Return the index of the parent */
/* Return -2100 if the parent index is invalid or unused */
int tree_parent(BTree *T, int child_index){
	/* Your code here */
	if (child_index <= 0 || child_index >= T->max_size) {
        return -2100;
	}

	int index = (child_index - 1) / 2;

	if (index < 0) {
        return -2100;
	}

	if (T->key[index] == INT_MAX) {
        return -2100;
	}

	return index;
}

/* Get the index of left child #5 */
/* Return the index of the left child */
/* Return -2100 if the left child index is invalid or unused */
int tree_lchild(BTree *T, int parent_index) {
	/* Your code here */
	if (parent_index < 0) {
        return -2100;
	}

    int index = 2 * parent_index + 1;
    if (index >= T->max_size || T->key[index] == INT_MAX) {
        return -2100;
	}
	return index;
}

/* Get the index of right child #6 */
/* Return the index of the right child */
/* Return -2100 if the right child index is invalid or unused */
int tree_rchild(BTree *T, int parent_index){
	/* Your code here */
	if (parent_index < 0) {
        return -2100;
	}

	int index = 2 * parent_index + 2;
    if (index >= T->max_size || T->key[index] == INT_MAX) {
        return -2100;
	}
	return index;
}

/* Insert or update a node #7 */
/* If key exists in T, update the value */
/* If key not in T, insert (key, double) as left child of parent_index*/
/* If the left child cannot be inserted, then do nothing */
/* If the left child is used by other key, then do nothing */
void tree_insert_lchild(BTree *T, int parent_index, int key, double value){
	/* Your code here */
	//update
	int i;
	for (i = 0; i < T->max_size; i++) {
        if (T->key[i] == key) {
            T->value[i] = value;
        }
	}

	//insert
	//invalid parent
	if (parent_index < 0) {
        return;
	}

	//already used
	if (tree_lchild(T, parent_index) != -2100) {
        return;
	}

	//insert allow
    int index = 2 * parent_index + 1;
    if (index >= T->max_size) {
        //invalid child indexs
        return;
    } else {
        T->key[index] = key;
        T->value[index] = value;
    }
}

/* Insert or update a node #8 */
/* If key exists in T, update the value */
/* If key not in T, insert (key,double) as right child of parent_index*/
/* If the right child cannot be inserted, then do nothing */
/* If the right child is used by other key, then do nothing */
void tree_insert_rchild(BTree *T, int parent_index, int key, double value){
	/* Your code here */
    //update
	int i;
	for (i = 0; i < T->max_size; i++) {
        if (T->key[i] == key) {
            T->value[i] = value;
        }
	}

	//insert
	//invalid parent
	if (parent_index < 0) {
        return;
	}

	//already used
	if (tree_rchild(T, parent_index) != -2100) {
        return;
	}

	//insert allow
    int index = 2 * parent_index + 2;
    if (index >= T->max_size) {
        //invalid child indexs
        return;
    } else {
        T->key[index] = key;
        T->value[index] = value;
    }
}

/* Find the value based on the key in the tree T or not #9 */
/* If key in T, return the corresponding value */
/* If key not in T, return -2100.00 */
double tree_key_find(BTree *T, int key){
	/* Your code here */
	int i;
	for (i = 0; i < T->max_size; i++) {
        if (T->key[i] == key) {
            return T->value[i];
        }
	}

	return -2100.00;
}

/* Find the value based on the index in the tree T or not #10 */
/* If index is used, return the corresponding value */
/* If index is unused or exceeding the max_size, return -2100.00 */
double tree_index_find(BTree *T, int index){
	/* Your code here */
	if (index < 0 || index >= T->max_size || T->key[index] == INT_MAX) {
        return -2100.00;
    }

    return T->value[index];
}

/* Free the tree *T, if *T is not NULL #11 */
/* Assign NULL to *T after free */
void tree_free(BTree **T){
	/* Your code here */
    free((*T)->key);
    free((*T)->value);
    free(*T);
    *T = NULL;
}

/* The print function print the tree in an output string using postorder traversal #12 */
/* The number in the bracket is key, number after bracket is value */
/* If the tree looks like */
/* (0)1.7 */
/* |       \ */
/* (1)1.2  (2)1.8  */
/* |        |     \ */
/* (4)0    (3)2   (6)5 */
/* Then, the output string is "(4)0.00 (1)1.20 (3)2.00 (6)5.00 (2)1.80 (0)1.70 " */
/* You can assume the number of nodes is not more than 100 */
void tree_print_recursive(BTree* T, int currIndex, char* output) {
    if (currIndex == -2100) return;

    tree_print_recursive(T, tree_lchild(T, currIndex), output);
    tree_print_recursive(T, tree_rchild(T, currIndex), output);

    sprintf(output, "%s(%d)%.2f \0", output, T->key[currIndex], T->value[currIndex]);
}

char *tree_print(BTree *T){
	char *output;
	/* Your code here */
    output = malloc(sizeof(char) * (11+20+3) * 100);
	tree_print_recursive(T, 0, output);
	return output;
}

