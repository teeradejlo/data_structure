#include"lab3-q2.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

/* Return a new empty stack #1 #9 */
/* An empty stack is data storing CHAR_MAX and next pointing to NULL */
void stack_init(Stack** s){
	/* Your code here */
    Stack* tmp = malloc(sizeof(Stack));
    stack_make_empty(tmp);
    *s = tmp;
}

/* Make the stack empty #2 */
void stack_make_empty(Stack* s){
	/* Your code here */
	memset(s, 0, sizeof(Stack));
    s->data = CHAR_MAX;
    s->next = NULL;
}

/* Return the size of the stack #3 */
int stack_size(Stack* s){
	/* Your code here */
	if (stack_is_empty(s)) return 0;

	Stack* dummy = s->next;
	int cnt = 0;
    while(dummy != NULL) {
        cnt++;
        dummy = dummy->next;
    }

	return cnt;
}

/* Check if the stack is empty #4 #9 */
/* Return 1 if empty, return 0 if not empty */
int stack_is_empty(Stack* s){
	/* Your code here */
	if (s->next == NULL) return 1;

	return 0;
}

/* Push the value x to the top of the stack #5 #9 */
void stack_push(Stack* s, char x){
	/* Your code here */
	Stack* tmp;
	stack_init(&tmp);
	tmp->data = x;

    if (stack_is_empty(s)) {
        s->next = tmp;
        return;
    }

    tmp->next = s->next;
    s->next = tmp;
}

/* Return the topmost element of the stack #6 #9 */
/* If the stack is empty, return 0 */
char stack_top(Stack* s){
	/* Your code here */
	if (stack_is_empty(s)) return 0;

	return (s->next)->data;
}

/* If s is not empty, pop an element from the stack #7 #9 */
void stack_pop(Stack* s){
	/* Your code here */
	Stack* dummy = s->next;
	if (stack_is_empty(s) == 0) {
        s->next = dummy->next;
        free(dummy);
	}
}

/* Free the stack, if the stack is not NULL #8 #9 */
/* Assign NULL to q after free */
void stack_free(Stack** s){
    /* Your code here */
    if (*s == NULL) return;

    if (stack_is_empty(*s)) {
        free(*s);
        *s = NULL;
        return;
    }

    Stack* dummy = (*s)->next;
    Stack* dummy2 = dummy->next;

    while (dummy2 != NULL) {
        free(dummy);
        dummy = dummy2;
        dummy2 = dummy->next;
    }
    free(dummy);
    dummy = NULL;
    free(*s);
    *s = NULL;
}

/* Print the stack in the format #9 #10 */
/* e.g. s: a b c d, where d is the topmost element */
/* output: "(top) d c b a" */
char* stack_print(Stack* s){
	char *output;
	/* Your code here */
	int len;
	len = stack_size(s) * 3 + 10;
	output = malloc(sizeof(char) * len);
	memset(output, 0, sizeof(char) * len);

	sprintf(output, "(top)\0");

    Stack* dummy = s->next;
    while (dummy != NULL) {
        sprintf(output, "%s %c\0", output, dummy->data);
        dummy = dummy->next;
    }

	return output;
}


