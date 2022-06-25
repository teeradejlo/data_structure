#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

/* Your code here */
#define MAX_SIZE 10000
struct queue{
	int data1[MAX_SIZE];
	int data2[MAX_SIZE];
    int front;
    int rear;
    int size;
};
typedef struct queue Queue;

/* Make the queue empty #2 */
/* An empty queue has 0 values for frosnt, rear and size */
void queue_make_empty(Queue* q){
	/* Your code here */
    memset(q->data1, 0, sizeof(q->data1));
    memset(q->data2, 0, sizeof(q->data2));
    q->front = 0;
    q->rear = 0;
    q->size = 0;
}

/* Return a new empty queue #1 #10 */
void queue_init(Queue** q) {
	/* Your code here */
    Queue* tmp = malloc(sizeof(Queue));
    queue_make_empty(tmp);
    *q = tmp;
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
void queue_enqueue(Queue* q, int x, int y){
	/* Your code here */
    if (queue_is_full(q)) return;

    q->data1[q->rear] = x;
    q->data2[q->rear] = y;
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->size++;
}

/* If q is not empty, dequeue and return the front of the queue #7 #10 */
/* If the queue is empty, return INT_MAX */
int queue_dequeue(Queue* q, int* x, int* y){
	/* Your code here */
	if (queue_is_empty(q)) return -1;

	*x = q->data1[q->front];
	*y = q->data2[q->front];

	q->front = (q->front + 1) % MAX_SIZE;
	q->size--;
    return 1;
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

int indexesTonum (int col, int x, int y) {
    return col * x + y;
}

void print_q(Queue *q, int col) {
    int size = queue_size(q);
    int index;
    for (int i = 0; i < size; i++) {
        index = (q->front + i) % MAX_SIZE;
        printf("[%4d] ", indexesTonum(col, q->data1[index], q->data2[index]));
    }
    printf("\n");
}

int main(int argc, char *argv[]) {

	FILE * fin, * fout;
	int i, j, k;
	int n, row, col;
	char maze[101][101];
	//right down left up
	int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	int ans = -1;

	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	fscanf(fin, "%d%d", &row, &col);
	n = row*col; /* total number of nodes */

	/* Reading input */
	for (i = 0; i < row; i++) {
		fscanf(fin, "%s", maze[i]);
		printf("%s\n", maze[i]); /* for testing purpose */
	}
	printf("\n\n");

	/* Your code here */
	Queue *bfs_q;
	queue_init(&bfs_q);

	int start_row = -1;
	int start_col = -1;
	int end_row = -1;
	int end_col = -1;
	int cnt = 0;

	int *depth = malloc(sizeof(int) * n);

	//number = col * i + j
	for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (maze[i][j] == 'S') {
                start_row = i;
                start_col = j;
            }
            if (maze[i][j] == 'E') {
                end_row = i;
                end_col = j;
            }
            depth[col * i + j] = -1;
        }
	}

    int solved = 0;

	if (start_row != -1 && start_col != -1 && end_row != -1 && end_col != -1) {
        queue_enqueue(bfs_q, start_row, start_col);
        depth[indexesTonum(col, start_row, start_col)] = cnt++;

        int curr_row = -1;
        int curr_col = -1;
        while (!queue_is_empty(bfs_q)) {
            print_q(bfs_q, col);
            queue_dequeue(bfs_q, &curr_row, &curr_col);

            int neig_row;
            int neig_col;
            for (int l = 0; l < 4; l++) {
                //right down left up
                neig_row = curr_row + dir[l][0];
                neig_col = curr_col + dir[l][1];
                cnt = depth[indexesTonum(col, curr_row, curr_col)] + 1;

                if (neig_row < 0 || neig_row >= row || neig_col < 0 || neig_col >= col) {
                    continue;
                }
                if (depth[indexesTonum(col, neig_row, neig_col)] == -1 || depth[indexesTonum(col, neig_row, neig_col)] == cnt) {
                    if (maze[neig_row][neig_col] == '.') {
                        depth[indexesTonum(col, neig_row, neig_col)] = cnt;
                        queue_enqueue(bfs_q, neig_row, neig_col);
                    } else if (maze[neig_row][neig_col] == 'E') {
                        depth[indexesTonum(col, neig_row, neig_col)] = cnt;
                        solved = 1;
                        break;
                    } else if (maze[neig_row][neig_col] == 'I') {
                        depth[indexesTonum(col, neig_row, neig_col)] = cnt;
                        neig_row += dir[l][0];
                        neig_col += dir[l][1];

                        while (neig_row >= 0 && neig_row < row && neig_col >= 0 && neig_col < col) {
                            if (depth[indexesTonum(col, neig_row, neig_col)] == -1)
                                depth[indexesTonum(col, neig_row, neig_col)] = cnt;
                            if (maze[neig_row][neig_col] == '.') {
                                queue_enqueue(bfs_q, neig_row, neig_col);
                                break;
                            }
                            if (maze[neig_row][neig_col] == 'X') {
                                depth[indexesTonum(col, neig_row, neig_col)] = -2;
                                neig_row -= dir[l][0];
                                neig_col -= dir[l][1];

                                queue_enqueue(bfs_q, neig_row, neig_col);
                                break;
                            }
                            if (maze[neig_row][neig_col] == 'E') {
                                solved = 1;
                                break;
                            }
                            neig_row += dir[l][0];
                            neig_col += dir[l][1];
                        }
                        if (solved) {
                            break;
                        }
                    } else if (maze[neig_row][neig_col] == 'X') {
                        depth[indexesTonum(col, neig_row, neig_col)] = -2;
                    }
                }
                if (solved) {
                    break;
                }
            }
            if (solved) {
                break;
            }
        }
    }

    printf("\nsolved = %d\n", solved);
    if (solved) {
        ans = depth[indexesTonum(col, end_row, end_col)];
    }

    printf("\n\n");
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++)
            printf("[%4d] ", depth[indexesTonum(col, i, j)]);
        printf("\n");
    }

    printf("\nans = %d\n", ans);

	/* Output format */
	if (ans != -1) {
		fprintf(fout, "I escape the maze in %d steps!\n", ans);
	} else {
		fprintf(fout, "I am tapped in the maze... QQ\n");
	}

	free(depth);
	queue_free(&bfs_q);
	fclose(fin);
	fclose(fout);

	return 0;
}
