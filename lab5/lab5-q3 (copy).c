#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* Your code here */
typedef struct tree_cs {
	int key;						/* key of the node */
	int value;						/* value stored in the node */
	struct tree_cs * first_child;	/* pointer to the first child */
	struct tree_cs * next_sibling;	/* pointer to the next sibling */
} Tree_CS;

/* Initialize the tree with a root #1 */
/* Return a new tree with initialized root as (key, value) */
void tree_init(Tree_CS **T, int key, int value){
	/* Your code here */
    Tree_CS *tmp = malloc(sizeof(Tree_CS));
    tmp->key = key;
    tmp->value = value;
    tmp->first_child = NULL;
    tmp->next_sibling = NULL;
    *T = tmp;
}

/* Find the value based on the key in the tree T #8 */
/* If key in T, return the node of key */
/* If key does not exist in T, return NULL */
Tree_CS* tree_find(Tree_CS *T, int key){
	/* Your code here */
	Tree_CS *tmp;
	if (T == NULL) return NULL;
	if (T->key == key) return T;

	tmp = tree_find(T->next_sibling, key);
	if (tmp != NULL) return tmp;
	return tree_find(T->first_child, key);
}


/* Check if key exist in the tree T or not #7 */
/* If key in T, return 1 */
/* If key not in T, return 0 */
int tree_contain(Tree_CS *T, int key){
	/* Your code here */
    if (tree_find(T,key) != NULL) return 1;
	return 0;
}

/* Insert (key, value) to the tree T #2 #3 */
/* If key already exist in T, then update the value */
/* If key does not exist in T, */
/* then add (key, value) to the last child of node with parent_key */
void tree_insert(Tree_CS *T, int parent_key, int key, int value){
	/* Your code here */
	Tree_CS *tmp, *newNode;
    if (tree_contain(T, key) == 1) {
        //update
        tmp = tree_find(T, key);
        tmp->value = value;
        return;
    }

    //insert
    if (tree_contain(T, parent_key) == 0) {
        //parent don't exist
        return;
    }
    tmp = tree_find(T, parent_key);
    newNode = malloc(sizeof(Tree_CS));
    newNode->key = key;
    newNode->value = value;
    newNode->first_child = NULL;
    newNode->next_sibling = NULL;
    if (tmp->first_child == NULL) {
        tmp->first_child = newNode;
        return;
    }
    tmp = tmp->first_child;
    while (tmp->next_sibling != NULL) {
        tmp = tmp->next_sibling;
    }
    tmp->next_sibling = newNode;
}

Tree_CS* tree_get_prev(Tree_CS *T, int key) {
    Tree_CS *tmp;
    if (T == NULL) return NULL;
    if (T->next_sibling != NULL && (T->next_sibling)->key == key) return T;
    if (T->first_child != NULL && (T->first_child)->key == key) return T;

    tmp = tree_get_prev(T->next_sibling, key);
    if (tmp != NULL) return tmp;
    return tree_get_prev(T->first_child, key);
}

int listParent(Tree_CS *T, int key, int* parent) {
    int currKey = key;
    int par_count = 0;
    Tree_CS *tmp = tree_find(T, key);
    Tree_CS *prev = tree_get_prev(T, key);

    //insert yourself into the list of parent
    parent[par_count] = currKey;
    par_count++;

    if (prev == NULL) {
        //key is at root (only itself as parent)
        printf("%d is a root\n", key);
        return par_count;
    }
    while (prev != T) {
        currKey = prev->key;
        if (prev->first_child == tmp) {
            printf("%d is parent of %d\n", currKey, key);
            parent[par_count] = currKey;
            par_count++;
        }
        prev = tree_get_prev(T, currKey);
        tmp = tree_find(T, currKey);
    }
    currKey = prev->key;
    printf("%d is a root\n", currKey);
    parent[par_count] = currKey;
    par_count++;
    return par_count;
}

/* Free the tree T, if T is not NULL #9 */
void tree_free(Tree_CS **T){
	/* Your code here */
    if (T==NULL) return;
    if ((*T) == NULL) return;
    if ((*T)->next_sibling != NULL)
        tree_free(&((*T)->next_sibling));
    if ((*T)->first_child != NULL)
        tree_free(&((*T)->first_child));
    free(*T);
    *T=NULL;
}

int main(int argc, char *argv[]){
	FILE *fin, *fout;
	int i, N;
	int p, n, root;
	//My code
	Tree_CS *T;
    T = NULL;

	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	/* read input, and construct tree */
	fscanf(fin, "%d", &N);
	for (i = 0; i < N - 1; i++) {
		fscanf(fin, "%d%d", &p, &n);
		if (i == 0) root = p;
		/* Your code here */
        if (i == 0) {
            tree_init(&T, p, p);
            tree_insert(T, p, n, n);
        } else {
            tree_insert(T, p, n, n);
        }
	}

	/* Your code here */
    int a, b;
    fscanf(fin, "%d%d", &a, &b);
    int *a_par = malloc(sizeof(int) * N);
    int *b_par = malloc(sizeof(int) * N);
    int a_par_length, b_par_length;
    for(int j = 0; j < N; j++) {
        a_par[j] = -1;
        b_par[j] = -1;
    }

    a_par_length = listParent(T, a, a_par);
    b_par_length = listParent(T, b, b_par);
    printf("%d %d\n", a_par_length, b_par_length);
    int found = 0;
    if (a == b) {
        found = 1;
        fprintf(fout, "%d\n", a);
        printf("lowest common ancestor: %d\n", a);
    } else if (a == root || b == root) {
        found = 1;
        fprintf(fout, "%d\n", root);
        printf("lowest common ancestor: %d\n", root);
    } else {
        for (int j = 0; j < a_par_length; j++) {
            for (int k = 0; k < b_par_length; k++) {
                if (a_par[j] == b_par[k]) {
                    fprintf(fout, "%d\n", b_par[k]);
                    printf("lowest common ancestor: %d\n", b_par[k]);
                    found = 1;
                    break;
                }
            }
            if (found) break;
        }
    }
    if (!found) {
        fprintf(fout, "\n");
        printf("lowest common ancestor: \n");
    }

    tree_free(&T);
    free(a_par);
    free(b_par);

	fclose(fin);
	fclose(fout);

	return 0;
}

