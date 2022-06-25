#include"lab7-q1.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>


/* Init an empty heap with a given size #1 */
void maxheap_init(MaxHeap **H, int maxsize){
	/* Your code here */
    MaxHeap *tmp = malloc(sizeof(MaxHeap));
    tmp->maxsize = maxsize;
    tmp->count = 0;
    tmp->data = malloc(sizeof(Node) * (maxsize+1));
    memset(tmp->data, 0, sizeof(Node) * (maxsize+1));

    *H = tmp;
}

/* Heaplify a max-heap based on the input array S with size S_size #2 #3 */
/* The root of heap is stored at H->node[1] */
/* Init the max-heap based on the input S */
void maxheap_heaplify(MaxHeap **H, Node* S, int S_size){
	/* Your code here */
    int i, index, swap, other, bigger;
    Node tmp;
    maxheap_init(H, S_size);
    for (i = 0; i < S_size; i++) {
        (*H)->data[i+1].key = S[i].key;
        sprintf((*H)->data[i+1].value, "%s\0", S[i].value);
    }
    (*H)->count = S_size;

    for (i = S_size/2; i > 0; i--) {
        tmp.key = (*H)->data[i].key;
        sprintf(tmp.value, "%s\0", (*H)->data[i].value);

        for (index = i; 1; index = bigger) {
            swap = (index << 1);
            other = swap | 1;
            if (swap > (*H)->count) break;
            if (other <= (*H)->count && (*H)->data[swap].key < (*H)->data[other].key)
                bigger = other;
            else bigger =swap;

            if (tmp.key > (*H)->data[bigger].key) break;
            (*H)->data[index].key = (*H)->data[bigger].key;
            sprintf((*H)->data[index].value, "%s\0", (*H)->data[bigger].value);
        }
        if (index != i) {
            //no swapping occur
            (*H)->data[index].key = tmp.key;
            sprintf((*H)->data[index].value, "%s\0", tmp.value);
        }
    }
}

/* Insert the (key,value) pair into the max-heap H #4 #5 #6 */
/* If key exist in the heap, update the value */
/* If key does not exist in the heap and heap is not full, */
/* perform the insertion of a max-heap */
/* If key does not exist in the heap but heap is full, do nothing */
/* Return 1 if insertion is successful */
/* Return 2 if update of value is successful */
/* Return 0 if heap is full and insertion cannot be proceeded */
int maxheap_insert(MaxHeap *H, int key, char* value) {
	/* Your code here */
    int index, parent, i;

    for (i = 1; i <= H->count; i++) {
        if (H->data[i].key == key) {
            sprintf(H->data[i].value, "%s\0", value);
            return 2;
        }
    }

    if (H->maxsize == H->count) return 0;

    H->count = H->count +1;
    for (index = H->count; index > 1; index = parent) {
        parent = (index >> 1);
        if (H->data[parent].key > key) break;
        H->data[index].key = H->data[parent].key;
        sprintf(H->data[index].value, "%s\0", H->data[parent].value);
    }
    H->data[index].key = key;
    sprintf(H->data[index].value, "%s\0", value);

	return 1;
}

/* Delete root of the max-heap #7 #8 */
/* Update the heap accordingly */
/* Return the (key,value) of the deleted root */
/* Return NULL if the heap is empty */
Node *maxheap_delete(MaxHeap *H) {
	/* Your code here */
    int i, index, swap, other, bigger, last;
    Node tmp, *result;

    if (H == NULL) return NULL;
    if (H->count == 0) return NULL;

    result = malloc(sizeof(Node));
    result->key = H->data[1].key;
    sprintf(result->value, "%s\0", H->data[1].value);

    last = H->count;
    tmp.key = H->data[last].key;
    sprintf(tmp.value, "%s\0", H->data[last].value);
    H->count = H->count - 1;

    for (index = 1; 1; index = bigger) {
        swap = (index << 1);
        other = swap | 1;
        if (swap > H->count) break;
        if (other <= H->count && H->data[swap].key < H->data[other].key)
            bigger = other;
        else bigger = swap;

        if (tmp.key > H->data[bigger].key) break;
        H->data[index].key = H->data[bigger].key;
        sprintf(H->data[index].value, "%s\0", H->data[bigger].value);
    }
    H->data[index].key = tmp.key;
    sprintf(H->data[index].value, "%s\0", tmp.value);

    return result;
}


/* Free the max-heap #9 */
/* Assign NULL pointer to *H */
void maxheap_free(MaxHeap **H) {
	/* Your code here */
    if (H == NULL) return;
    if ((*H) == NULL) return;
    free((*H)->data);
    free((*H));
    *H = NULL;
}

