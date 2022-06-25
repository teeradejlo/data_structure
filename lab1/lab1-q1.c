#include"lab1-q1.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define EPS 1e-4

/* Initialize the linked list as an empty list #1 */
void list_init_empty(Node **list){
	// Your code here
	*list = NULL;
}

/* Initialize the linked list with an array of n elements #2 */
/* The last element of the arr is the first element in the linked list*/
void list_init(Node **list, double *arr, int n){
	// Your code here
    Node *tmplist = NULL;

    int i;
    for (i = 0; i < n; i++) {
        tmplist = list_insert(tmplist, arr[i]);
    }

    *list = tmplist;
}

/* Insert value to the front of the linked list #3 #4 */
/* Return the head of the linked list */
Node* list_insert(Node *list, double value){
	// Your code here
    Node *tmplist = malloc(sizeof(Node));
    tmplist->value = value;
    tmplist->next = list;

	return tmplist;
}

/* Delete value from the linked list #5 #6 #7 */
/* If value is in the list, then delete it */
/* Note: there can be multiple value, you need to delete all of them */
/* If value is not in the list, then do nothing */
/* Return the head of the linked list */
Node* list_delete(Node *list, double value){
	// Your code here
	Node *tmplist = list, *prev = NULL;

    while (tmplist != NULL) {
        if(fabs(tmplist->value - value) < EPS) {
            if (prev == NULL) {
                list = list->next;
                free(tmplist);
                tmplist = list;
                continue;
            } else {
                prev->next = tmplist->next;
                free(tmplist);
                tmplist = prev->next;
                continue;
            }
        }
        prev = tmplist;
        tmplist = tmplist->next;
    }

	return list;
}

/* Check if value exists in the list or not #8 */
/* If value is in the list, return 1 */
/* If value is not in the list, return 0 */
int list_contain(Node *list, double value){
	// Your code here
    Node *tmp;
    for (tmp = list; tmp != NULL; tmp = tmp->next) {
        if(fabs(tmp->value - value) < EPS) {
            return 1;
        }
    }

	return 0;
}

/* Free the list, if list is not NULL #9 */
/* Assign NULL to the *list */
void list_free(Node **list){
	// Your code here
    if (*list == NULL) return;

    list_free(&((*list)->next));
    free(*list);
    *list = NULL;
}

/* The print function print the list in an output string #10 */
/* Example: "14.00 15.00 17.50 " */
/* You can assume the number of nodes is not more than 100 */
/* You can assume the largest value is capped by 100 */
char* list_print(Node *list){
	// Your code here
	int maxlen = 101*100;
	char *output = malloc(sizeof(char) * maxlen);

	Node *ptr = list;
	memset(output, 0, sizeof(char) * maxlen);

	for (ptr = list; ptr != NULL; ptr=ptr->next) {
        sprintf(output, "%s%.2f ", output, ptr->value);
	}

	return output;
}

