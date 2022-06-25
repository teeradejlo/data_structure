#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<math.h>

struct node {
	char data;
    struct node *next;
};
typedef struct node Stack;

void stack_make_empty(Stack* s){
	/* Your code here */
	memset(s, 0, sizeof(Stack));
    s->data = CHAR_MAX;
    s->next = NULL;
}

void stack_init(Stack** s){
	/* Your code here */
    Stack* tmp = malloc(sizeof(Stack));
    stack_make_empty(tmp);
    *s = tmp;
}

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

int main (int argc, char *argv[]){

	FILE * fin, *fout;
	int i, len;
	char s[102];
	int count = 0;
	int error = -1;

	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	/* initialization of variables */
	memset(s,0,sizeof(s));

	/* input */
	fscanf(fin, "%s", s);
	len = strlen(s);

	/* Your code here */
	Stack* open;
	stack_init(&open);
	int statuserr = 0;

    for (i = 0; i < len; i++) {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
            stack_push(open, s[i]);
        } else {
            switch (stack_top(open)) {
                case '(':
                    if (s[i] == ')') {
                        stack_pop(open);
                        count++;
                    } else {
                        statuserr = 1;
                    }
                    break;
                case '{':
                    if (s[i] == '}') {
                        stack_pop(open);
                        count++;
                    } else {
                        statuserr = 1;
                    }
                    break;
                case '[':
                    if (s[i] == ']') {
                        stack_pop(open);
                        count++;
                    } else {
                        statuserr = 1;
                    }
                    break;
                case 0:
                    statuserr = 1;
                    break;
            }
            if (statuserr == 1) {
                error = i;
                break;
            }
        }
    }
    if (!statuserr && !stack_is_empty(open)) {
        error = len;
    }
    stack_free(&open);


	/* output format, you may need to edit the variables */
	if (error == -1) {
		fprintf(fout, "There are %d balanced parentheses.", count);
	} else {
		fprintf(fout, "Error is spot at position %d at first.", error);
	}


	fclose(fin);
	fclose(fout);

	return 0;
}
