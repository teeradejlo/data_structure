/* lab3-q1.h */

/* Cannot modify: struct queue, MAX_SIZE */
#define MAX_SIZE 100
struct queue{
	int data[MAX_SIZE];
    int front;
    int rear;
    int size;
};
typedef struct queue Queue;

/* Return a new empty queue #1 #10 */
void queue_init(Queue** q);

/* Make the queue empty #2 */
/* An empty queue has 0 values for front, rear and size */
void queue_make_empty(Queue* q);

/* Return the size of the queue #3 */
int queue_size(Queue* q);

/* Check if the queue is empty #4 */
/* Return 1 if empty, return 0 if not empty */
int queue_is_empty(Queue* q);

/* Check if the queue is full #5 */
/* Return 1 if full, return 0 if not full */
int queue_is_full(Queue* q);

/* If the queue is not full, enqueue the value x to the rear of the queue #6 #10 */
void queue_enqueue(Queue* q, int x);

/* If q is not empty, dequeue and return the front of the queue #7 #10 */
/* If the queue is empty, return INT_MAX */
int queue_dequeue(Queue* q);

/* Free the queue, if the queue is not NULL #8 #10 */
/* Assign NULL to q after free */
void queue_free(Queue** q);

/* Print the stack in the format #9 #10 */
/* e.g. q: 0 1 2 3, where 0 is the front */
/* output: "(front) 0 1 2 3 (rear)" */
char* queue_print(Queue* q);
