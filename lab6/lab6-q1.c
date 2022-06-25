#include"lab6-q1.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

/* Init an empty BST #1 */
void bst_init(BST **T){
	/* Your code here */
    *T = NULL;
}

/* Create a new node with specified values #2 */
/* Set the children to NULL */
BST* bst_create_node(int key, int value){
	/* Your code here */
    BST* tmp = malloc(sizeof(BST));

    tmp->key = key;
    tmp->value = value;
    tmp->lchild = NULL;
    tmp->rchild = NULL;

	return tmp;
}

/* Search for key in the tree #3 */
/* Return the node with the key */
/* Return NULL if the key does not exist in the tree */
BST *bst_find(BST *T, int key){
	/* Your code here */
    if (T == NULL) return NULL;
    if (key < T->key) return bst_find(T->lchild, key);
    if (key > T->key) return bst_find(T->rchild, key);

    return T;
}

/* Insert the (key,value) pair into the tree #4 #5 */
/* If key exist in the tree, update the value */
/* If key does not exist in the tree, create the new node and add to the tree */
/* Return the root of the tree */
BST* bst_insert(BST *T, int key, int value){
	/* Your code here */
    if (T == NULL) {
        T = bst_create_node(key, value);
    }
    else if (key < T->key) {
        T->lchild = bst_insert(T->lchild, key, value);
    }
    else if (key > T->key) {
        T->rchild = bst_insert(T->rchild, key, value);
    } else {
        T->value = value;
    }

    return T;
}

/* Delete the node with specified key #6 #7 #8 */
/* If key does not exist in the tree, do nothing */
/* If key is leaf, delete it directly */
/* If key has one child, adjust a pointer to bypass this node and delete it */
/* If key has two children, replace the (key,value) of this node with the largest (key,value) of the left subtree, and propagate the deletion */
/* Return the root of the tree */
BST *bst_delete(BST *T, int key){
	/* Your code here */
    if (T == NULL) {
        return NULL;
    } else if (key < T->key) {
        T->lchild = bst_delete(T->lchild, key);
    } else if (key > T->key) {
        T->rchild = bst_delete(T->rchild, key);
    } else {
        if (T->lchild != NULL && T->rchild != NULL) {
            BST* tmp = bst_find_max(T->lchild);
            T->key = tmp->key;
            T->value = tmp->value;
            T->lchild = bst_delete(T->lchild, tmp->key);
        } else {
            BST* tmp = T;
            if (T->lchild != NULL) {
                T = T->lchild;
            } else {
                T = T->rchild;
            }
            free(tmp);
        }
    }

    return T;
}

/* Find the node storing maximum key among all nodes in the tree #9 */
BST *bst_find_max(BST *T){
	/* Your code here */
    if (T == NULL) return T;
    if (T->rchild != NULL) return bst_find_max(T->rchild);
    return T;
}

/* Free the tree #10 */
/* Assign NULL pointer to *T */
void bst_free(BST **T){
	/* Your code here */
	if (T == NULL) return;
	if ((*T) == NULL) return;
	if ((*T)->lchild != NULL) bst_free(&((*T)->lchild));
	if ((*T)->rchild != NULL) bst_free(&((*T)->rchild));

    free(*T);
    *T = NULL;
}

