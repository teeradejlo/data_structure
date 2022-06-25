/* lab3-q2.h */

/* Cannot modify: struct node, Stack */
struct node {
	char data;
    struct node *next;
};
typedef struct node Stack;

/* Return a new empty stack #1 #9 */
/* An empty stack is data storing CHAR_MAX and next pointing to NULL */
void stack_init(Stack** s);

/* Make the stack empty #2 */
void stack_make_empty(Stack* s);

/* Return the size of the stack #3 */
int stack_size(Stack* s);

/* Check if the stack is empty #4 */
/* Return 1 if empty, return 0 if not empty */
int stack_is_empty(Stack* s);

/* Push the value x to the top of the stack #5 #9 */
void stack_push(Stack* s, char x);

/* Return the topmost element of the stack #6 #9 */
/* If the stack is empty, return 0 */
char stack_top(Stack* s);

/* If s is not empty, pop an element from the stack #7 #9 */
void stack_pop(Stack* s);

/* Free the stack, if the stack is not NULL #8 #9 */
/* Assign NULL to q after free */
void stack_free(Stack** s);

/* Print the stack in the format #9 #10 */
/* e.g. s: a b c d, where d is the topmost element */
/* output: "(top) d c b a" */
char* stack_print(Stack* s);
