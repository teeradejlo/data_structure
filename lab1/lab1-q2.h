// lab1-q2.h
// Cannot modify this file

typedef struct _list {
	char word[100][51];	/* The 2D array for words */
	int first, last;	      /* Index for the first and last position */
} CircularList;

/* Initialize the circular list as an empty list #1 */
/* first and last are set to 0 */
void circularlist_init_empty(CircularList **list);

/* Initialize the circular list with an array of n words #2 */
/* The last element of the arr is the last element in the list */
/* Suppose n < 100 */
void circularlist_init(CircularList **list, char arr[100][51], int n);

/* Insert value to the end of the list #3 #4 */
/* If list is full, then do nothing */
void circularlist_insert(CircularList *list, char *word);

/* Delete the first word from the list #5 #6 */
/* If list is empty, then do nothing and return null pointer */
/* Return the deleted word for non-empty list */
char* circularlist_deletefirst(CircularList *list);

/* Delete the last word from the list #7 #8 */
/* If list is empty, then do nothing and return null pointer */
/* Return the deleted word for non-empty list */
char* circularlist_deletelast(CircularList *list);

/* Return the size of the list #9 */
/* Note: The return value ranges from 0 and 99 inclusively */
int circularlist_size(CircularList *list);

/* Free the list, if list is not NULL #10 */
/* Assign NULL to the *list */
void circularlist_free(CircularList **list);

/* The print function print the list in an output string #11 */
/* Example: "haha Hello Yes " */
/* You can assume the number of nodes is not more than 99 */
char* circularlist_print(CircularList *list);

