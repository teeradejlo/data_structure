/* lab6-q2.h */
/* Cannot modify this file */
typedef struct et{
	char symbol; /* the operator of this node */
	char name; /* the name of this node, 'a'-'z' */
    int value; /* the result of this node */
    struct et *lchild, *rchild; /* the two children ptr of the node */
}ET;

/* Init an empty ET #1 */
void et_init(ET **T);

/* Create a new node with specified values #2 */
/* Set the children to NULL */
ET* et_create_node(char symbol, char name, int value);

/* Search for name in the tree #3 */
/* Return the node with the matched name */
/* Return NULL if the name does not exist in the tree */
ET *et_find(ET *T, char name); 

/* Update the tree based on the name of node #4 */
/* Update the symbol of this node */
/* Set the value to INT_MIN */
/* Add left child and right child to this node, with the given names */
/* Think about the initial symbol and initial value for the children */
/* Return this node if name is found */
/* Return NULL if name is not found */
ET* et_update_symbol(ET *T, char symbol, char name, char lchild_name, char rchild_name);
	
/* Update the tree based on the name of node #5 */
/* Update the value of this node */
/* Set the symbol of this node to '#' */
/* Return this node if name is found */
/* Return NULL if name is not found */
ET* et_update_value(ET *T, char name, int value);
	
/* Evaluate the tree #7 #8 #9 #10 */
/* Store the intermediate results as the value in all the internal node */
/* Return the result of the evaluation */
/* Return INT_MIN for any errors encountered */
int et_evaluate(ET *T);

/* Evaluate the calculation: value1 symbol value2 #6 */
/* +: addition 6+2=8 */
/* -: subtraction 6-2=4 */
/* *: multiplication 6*2=12 */
/* /: integer division 6/2=3 */
/* %: modulo division 6%2=0 */
/* &: bitwise-and 6&2=110%010=010=2 */
/* |: bitwise-or  6|2=110|010=110=6 */
/* ^: bitwise-xor 6^2=110^010=100=4 */
/* Return INT_MIN for invalid symbol */
int evaluate(char symbol, int value1, int value2);

/* Free the tree #11 */
/* Assign NULL pointer to *T */
void et_free(ET **T);



