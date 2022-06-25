#include"lab3-q1.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

/* Return a new empty queue #1 #10 */
void queue_init(Queue** q) {
	/* Your code here */
    Queue* tmp = malloc(sizeof(Queue));
    queue_make_empty(tmp);
    *q = tmp;
}

/* Make the queue empty #2 */
/* An empty queue has 0 values for frosnt, rear and size */
void queue_make_empty(Queue* q){
	/* Your code here */
    memset(q->data, 0, sizeof(q->data));
    q->front = 0;
    q->rear = 0;
    q->size = 0;
}

/* Return the size of the queue #3 */
int queue_size(Queue* q) {
    /* Your code here */
	return q->size;
}

/* Check if the queue is empty #4 */
/* Return 1 if empty, return 0 if not empty */
int queue_is_empty(Queue* q){
    /* Your code here */
    if (queue_size(q) == 0) {
        return 1;
    }
	return 0;
}

/* Check if the queue is full #5 */
/* Return 1 if full, return 0 if not full */
int queue_is_full(Queue* q){
	/* Your code here */
    if (queue_size(q) == MAX_SIZE) {
        return 1;
    }
	return 0;
}

/* If the queue is not full, enqueue the value x to the rear of the queue #6 #10 */
void queue_enqueue(Queue* q, int x){
	/* Your code here */
    if (queue_is_full(q)) return;

    q->data[q->rear] = x;
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->size++;
}

/* If q is not empty, dequeue and return the front of the queue #7 #10 */
/* If the queue is empty, return INT_MAX */
int queue_dequeue(Queue* q){
	/* Your code here */
	if (queue_is_empty(q)) return INT_MAX;

	int tmp = q->data[q->front];
	q->front = (q->front + 1) % MAX_SIZE;
	q->size--;

    return tmp;
}

/* Free the queue, if the queue is not NULL #8 #10*/
/* Assign NULL to q after free */
void queue_free(Queue** q) {
	/* Your code here */
    if (q == NULL) return;
    if (*q == NULL) return;

    free(*q);
    *q = NULL;
}

/* Print the stack in the format #9 #10 */
/* e.g. q: 0 1 2 3, where 0 is the front */
/* output: "(front) 0 1 2 3 (rear)" */
char* queue_print(Queue* q){
	char *output;
	/* Your code here */
	int len, i, cnt;
	len = queue_size(q) * 13 + 15;
	output = malloc(sizeof(char) * len);
	memset(output, 0, sizeof(char) * len);

	sprintf(output, "(front)\0");
	for (i = q->front, cnt = 0; cnt != q->size; i = (i+1) % MAX_SIZE, cnt++) {
        sprintf(output, "%s %d\0", output, q->data[i]);
	}
	sprintf(output, "%s (rear)\0", output);

	return output;
}

