#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

/* You can implement some functions */
/* You may edit and reuse some code in lab1-q1 or lab1-q2 */
/* We only accept a single c file, no multiple files for 1 question */

typedef struct __node {
	struct __node* prev;
	struct __node* next;
	int value;
} Node;

void list_init(Node **list, int value) {
    Node* dummy = *list;
    for (int i = 0; i < value; i++) {
        dummy->value = i+1;
        dummy->next = (Node*)malloc(sizeof(Node));
        (dummy->next)->prev = dummy;
        dummy = dummy->next;
    }
    (dummy->prev)->next = *list;
    (*list)->prev = dummy->prev;
    free(dummy);
    dummy = NULL;
}

Node* deleteNode(Node **ptr) {
    Node* dummy;
    ((*ptr)->prev)->next = (*ptr)->next;
    ((*ptr)->next)->prev = (*ptr)->prev;
    dummy = (*ptr)->next;
    free(*ptr);
    *ptr = NULL;
    return dummy;
}


int main(int argc, char *argv[]) {

	FILE *fin, *fout;
	int n, k;

	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");
	fscanf(fin, "%d%d", &n, &k);

	/* Your code here */
	Node* listhead = malloc(sizeof(Node));
	list_init(&listhead, n);

    int i;
	for (i = 0; i < n; i++) {
        for (int j = 0; j < k - 1; j++) {
            listhead = listhead->next;
        }
        fprintf(fout, "%d", listhead->value);
        listhead = deleteNode(&listhead);
        if (i < n-1) {
            fprintf(fout, " ");
        }
	}
	fprintf(fout, "\n");

	fclose(fin);
	fclose(fout);

	return 0;
}


