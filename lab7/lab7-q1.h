/* lab7-q1.h */
/* Cannot modify this file */
typedef struct node {
	int key;			/* key of a node */
	char value[100];	/* value of a node */
} Node;

typedef struct heap{
	int maxsize;	/* maximum size of the heap */
	int count; 		/* number of nodes stored in the heap */
	Node *data;		/* storage of the heap */
}MaxHeap; 


/* Init an empty heap with a given size #1 */
void maxheap_init(MaxHeap **H, int maxsize);

/* Heaplify a max-heap based on the input array S with size S_size #2 #3 */
/* The root of heap is stored at H->node[1] */
/* Init the max-heap based on the input S */
void maxheap_heaplify(MaxHeap **H, Node* S, int S_size); 

/* Insert the (key,value) pair into the max-heap H #4 #5 #6 */
/* If key exist in the heap, update the value */
/* If key does not exist in the heap and heap is not full, */
/* perform the insertion of a max-heap */
/* If key does not exist in the heap but heap is full, do nothing */
/* Return 1 if insertion is successful */
/* Return 2 if update of value is successful */
/* Return 0 if heap is full and insertion cannot be proceeded */
int maxheap_insert(MaxHeap *H, int key, char* value);
	
/* Delete root of the max-heap #7 #8 */
/* Update the heap accordingly */
/* Return the (key,value) of the deleted root */
/* Return NULL if the heap is empty */
Node *maxheap_delete(MaxHeap *H);


/* Free the max-heap #9 */
/* Assign NULL pointer to *H */
void maxheap_free(MaxHeap **H);

