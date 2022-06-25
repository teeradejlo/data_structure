#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* You can start your program without using this skeleton */

typedef struct tree_cs {
	char word[82];					/* key of the node */
	struct tree_cs * first_child;	/* pointer to the first child */
	struct tree_cs * next_sibling;	/* pointer to the next sibling */
} Tree_CS;

/* You need to reuse lab2-q2.c */
/* Copy your code below */
int compare(char *A, char *B) {
	/* Your code here */
	int A_index = 0, B_index = 0;
	int Acopy_index = 0, Bcopy_index = 0;
	int found_res = 0;
	char Acopy[82] = { 0, };
    char Bcopy[82] = { 0, };

	while (A_index < 82 && B_index < 82) {
        //copy word to _copy
        while (A[A_index] != '\\' && A[A_index] != 0) {
            Acopy[Acopy_index] = A[A_index];
            Acopy_index++;
            A_index++;
        }

        while (B[B_index] != '\\' && B[B_index] != 0) {
            Bcopy[Bcopy_index] = B[B_index];
            Bcopy_index++;
            B_index++;
        }

        //if not same word return cmp
        if (strcmp(Acopy, Bcopy) != 0) {
            return strcmp(Acopy, Bcopy);
        }
        //same word and need to continue compare
        if (A[A_index] == '\\' && B[B_index] == '\\') {
            A_index++;
            B_index++;
        } else {
            //one of the word already end
            return A[A_index] - B[B_index];
        }

        Acopy_index = 0;
        Bcopy_index = 0;
        memset(Acopy, 0, sizeof(char) * 82);
        memset(Bcopy, 0, sizeof(char) * 82);
	}

	return 0;
}

/* Insersion sort algorithm */
void insertionsort(int n, char ** a){
    int i, j;
	char *tmpptr;

	for (i = 1; i < n; i++) {
		/* Your code here */
        tmpptr = a[i];

        for (j = i; j > 0 && compare(a[j-1], tmpptr) > 0; j--) {
            a[j] = a[j-1];
        }
        a[j] = tmpptr;
	}
}


/* You also need to reuse lab5-q1.c */
/* Copy your code below */
/* Then, the contain stored in node is changed to char array, i.e. word */
/* Your also need to edit the insert function */
/* Initialize the tree with a root #1 */
/* Return a new tree with initialized root as (key, value) */
void tree_init(Tree_CS **T, char* word){
	/* Your code here */
    Tree_CS *tmp = malloc(sizeof(Tree_CS));
    memset(tmp->word, 0, sizeof(char) * 82);
    strcpy(tmp->word, word);
    tmp->first_child = NULL;
    tmp->next_sibling = NULL;
    *T = tmp;
}

/* Find the value based on the key in the tree T #8 */
/* If key in T, return the node of key */
/* If key does not exist in T, return NULL */
Tree_CS* tree_find(Tree_CS *T, char* word){
	/* Your code here */
	Tree_CS *tmp;
	if (T == NULL) return NULL;
	if (strcmp(T->word, word) == 0) return T;

	tmp = tree_find(T->next_sibling, word);
	if (tmp != NULL) return tmp;
	return tree_find(T->first_child, word);
}

/* Check if key exist in the tree T or not #7 */
/* If key in T, return 1 */
/* If key not in T, return 0 */
int tree_contain(Tree_CS *T, char* word){
	/* Your code here */
    if (tree_find(T,word) != NULL) return 1;
	return 0;
}

/* Insert (key, value) to the tree T #2 #3 */
/* If key already exist in T, then update the value */
/* If key does not exist in T, */
/* then add (key, value) to the last child of node with parent_key */
void tree_insert(Tree_CS *T, char* par_word, char* child_word){
	/* Your code here */
	Tree_CS *tmp, *newNode;

	//parent always exist
	if (tree_contain(tree_find(T, par_word), child_word)) {
        //child already exist;
        return;
	}

    //insert
    tmp = tree_find(T, par_word);
    newNode = malloc(sizeof(Tree_CS));
    memset(newNode->word, 0, sizeof(char) * 82);
    strcpy(newNode->word, child_word);
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

void tree_print(Tree_CS *T, int level, FILE* fout) {
    if (T == NULL) {
        return;
    }
    printf("%*s%s\n", level, "", T->word);
    fprintf(fout, "%*s%s\n", level, "", T->word);
    tree_print(T->first_child, level+1, fout);
    tree_print(T->next_sibling, level, fout);
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
    char **path;
    int n, i;

	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	/* Read input */
	fscanf(fin, "%d", &n);
	path = malloc(sizeof(char*)*n);
	for (i = 0; i < n; i++){
		path[i] = malloc(sizeof(char)*82);
		memset(path[i], 0, sizeof(char)*82);
		fscanf(fin, "%s", path[i]);
		printf("%s\n", path[i]);
	}

    printf("\n");
	/* Your code here */
	/* Sort the path first */
    insertionsort(n, path);
    for (i = 0; i < n; i++) {
        printf("%s\n", path[i]);
	}
	printf("\n");

	/* Construct trees */
	char root[] = "root";
    Tree_CS *T;
    tree_init(&T, root);

    for (i = 0; i < n; i++) {
        char* token = strtok(path[i], "\\");
        char* dummy = root;
        printf("Query %d:\n", i);
        while (token != NULL) {
            tree_insert(T, dummy, token);
            printf("%s -> %s\n", dummy, token);
            dummy = token;
            token = strtok(NULL, "\\");
        }
        printf("\n");
    }

	/* Output trees */
    tree_print(T->first_child, 0, fout);

    for (i = 0; i < n; i++) {
        free(path[i]);
    }
    free(path);

    tree_free(&T);
	fclose(fin);
	fclose(fout);

	return 0;
}

