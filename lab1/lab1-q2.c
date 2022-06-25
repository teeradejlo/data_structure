#include"lab1-q2.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

/* Initialize the circular list as an empty list #1 */
/* first and last are set to 0 */
void circularlist_init_empty(CircularList **list){
	// Your code here
    CircularList *tmplist = malloc(sizeof(CircularList));
    tmplist->first = 0;
    tmplist->last = 0;
    memset(tmplist->word, 0, sizeof(char) * 51 * 100);
    *list = tmplist;
}

/* Initialize the circular list with an array of n words #2 */
/* The last element of the arr is the last element in the list */
/* Suppose n < 100 */
void circularlist_init(CircularList **list, char arr[100][51], int n){
	// Your code here
    circularlist_init_empty(list);

    int i;
    for (i = 0; i < n; i++) {
        circularlist_insert(*list, arr[i]);
    }
}

/* Insert value to the end of the list #3 #4 */
/* If list is full, then do nothing */
void circularlist_insert(CircularList *list, char *word){
	// Your code here
	if(circularlist_size(list) == 99) return;

    strcpy(list->word[list->last], word);
    list->last = (list->last+1) % 100;
}

/* Delete the first word from the list #5 #6 */
/* If list is empty, then do nothing and return null pointer */
/* Return the deleted word for non-empty list */
char* circularlist_deletefirst(CircularList *list){
	// Your code here
	if (circularlist_size(list) == 0) {
        return NULL;
	} else {
        char* tmp;
        strcpy(tmp, list->word[list->first]);
        memset(list->word[list->first], 0, 50 * sizeof(char));
        list->first = (list->first+1) % 100;
        return tmp;
	}
}

/* Delete the last word from the list #7 #8 */
/* If list is empty, then do nothing and return null pointer */
/* Return the deleted word for non-empty list */
char* circularlist_deletelast(CircularList *list){
	// Your code here
    if (circularlist_size(list) == 0) {
        return NULL;
	} else {
        char* tmp;
        if (list->last == 0) {
            strcpy(tmp, list->word[99]);
            memset(list->word[99], 0, 51 * sizeof(char));
            list->last = 99;
            return tmp;
        }
        strcpy(tmp, list->word[list->last-1]);
        memset(list->word[list->last-1], 0, 51 * sizeof(char));
        list->last--;
        return tmp;
	}
}

/* Return the size of the list #9 */
/* Note: The return value ranges from 0 and 99 inclusively */
int circularlist_size(CircularList *list){
	// Your code here
	if (list->first <= list->last) {
        return list->last - list->first;
    } else {
        return (99-list->first) + list->last + 1;
    }
}

/* Free the list, if list is not NULL #10 */
/* Assign NULL to the *list */
void circularlist_free(CircularList **list){
	// Your code here
    if (*list == NULL) return;

    memset((*list)->word, 0, sizeof(char) * 51 * 100);
    free(*list);
    *list = NULL;
}

/* The print function print the list in an output string #11 */
/* Example: "haha Hello Yes " */
/* You can assume the number of nodes is not more than 99 */
char* circularlist_print(CircularList *list){
	// Your code here
	int maxlen = 51*100;
	char *output = malloc(sizeof(char) * maxlen);
	memset(output, 0, sizeof(char) * maxlen);

	int i, j;
	j = list->first;

	for (i = 1; i <= circularlist_size(list); i++) {
        sprintf(output, "%s%s ", output, list->word[j]);
        j =(j+1) % 100;
	}

	return output;
}
