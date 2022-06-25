#include"lab6-q2.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

/* Init an empty ET #1 */
void et_init(ET **T){
	/* Your code here */
	*T = NULL;
}

/* Create a new node with specified values #2 */
/* Set the children to NULL */
ET* et_create_node(char symbol, char name, int value){
	/* Your code here */
    ET* tmp = malloc(sizeof(ET));
    tmp->symbol = symbol;
    tmp->name = name;
    tmp->value = value;
    tmp->lchild = NULL;
    tmp->rchild = NULL;

	return tmp;
}

/* Search for name in the tree #3 */
/* Return the node with the matched name */
/* Return NULL if the name does not exist in the tree */
ET *et_find(ET *T, char name){
	/* Your code here */
	if (T == NULL) return NULL;
    if (T->name == name) return T;

    ET* tmp = NULL;
    tmp = et_find(T->lchild, name);
    if (tmp != NULL) return tmp;

    tmp = et_find(T->rchild, name);
    if (tmp != NULL) return tmp;

    return NULL;
}

/* Update the tree based on the name of node #4 */
/* Update the symbol of this node */
/* Set the value to INT_MIN */
/* Add left child and right child to this node, with the given names */
/* Think about the initial symbol and initial value for the children */
/* Return this node if name is found */
/* Return NULL if name is not found */
ET* et_update_symbol(ET *T, char symbol, char name, char lchild_name, char rchild_name){
	/* Your code here */
	ET* tmp = et_find(T, name);
	if (tmp != NULL) {
        tmp->symbol = symbol;
        tmp->value = INT_MIN;
        tmp->lchild = et_create_node('#', lchild_name, INT_MIN);
        tmp->rchild = et_create_node('#', rchild_name, INT_MIN);
        return tmp;
	} else {
        return NULL;
	}
}

/* Update the tree based on the name of node #5 */
/* Update the value of this node */
/* Set the symbol of this node to '#' */
/* Return this node if name is found */
/* Return NULL if name is not found */
ET* et_update_value(ET *T, char name, int value){
	/* Your code here */
    ET* tmp = et_find(T, name);
	if (tmp != NULL) {
        tmp->value = value;
        tmp->symbol = '#';
        return tmp;
	} else {
        return NULL;
	}
}

/* Evaluate the tree #7 #8 #9 #10 */
/* Store the intermediate results as the value in all the internal node */
/* Return the result of the evaluation */
/* Return INT_MIN for any errors encountered */
int et_evaluate(ET *T){
	/* Your code here */
    if (T->symbol != '#') {
        if (T->lchild == NULL || T->rchild == NULL) {
            return INT_MIN;
        }
        (T->lchild)->value = et_evaluate(T->lchild);
        if ((T->lchild)->value == INT_MIN) return INT_MIN;

        (T->rchild)->value = et_evaluate(T->rchild);
        if ((T->rchild)->value == INT_MIN) return INT_MIN;

        return evaluate(T->symbol, (T->lchild)->value, (T->rchild)->value);
    } else {
        return T->value;
    }
}

/* Evaluate the calculation: value1 symbol value2 #6 */
/* +: addition 6+2=8 */
/* -: subtraction 6-2=4 */
/* *: multiplication 6*2=12 */
/* /: integer division 6/2=3 */
/* %: modulo division 6%2=0 */
/* &: bitwise-and 6&2=110%010=010=2 */
/* |: bitwise-or  6|2=110|010=110=6 */
/* ^: bitwise-xor 6^2=110^010=100=4 */
/* Return INT_MIN for invalid symbol */
int evaluate(char symbol, int value1, int value2){
	/* Your code here */
	if (symbol == '+') {
        return value1 + value2;
	}
	if (symbol == '-') {
        return value1 - value2;
	}
	if (symbol == '*') {
        return value1 * value2;
	}
	if (symbol == '/') {
        return value1 / value2;
	}
	if (symbol == '%') {
        return value1 % value2;
	}
	if (symbol == '&') {
        return value1 & value2;
	}
	if (symbol == '|') {
        return value1 | value2;
	}
	if (symbol == '^') {
        return value1 ^ value2;
	}

	return INT_MIN;
}

/* Free the tree #11 */
/* Assign NULL pointer to *T */
void et_free(ET **T){
	/* Your code here */
    if (T == NULL) return;
	if ((*T) == NULL) return;
	if ((*T)->lchild != NULL) et_free(&((*T)->lchild));
	if ((*T)->rchild != NULL) et_free(&((*T)->rchild));

    free(*T);
    *T = NULL;
}



