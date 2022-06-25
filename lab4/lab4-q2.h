/* lab4-q2.h */
/* Cannot modify this file */

typedef struct node {
	int key;
	int value;
} Node;

typedef struct hash_os {
	int size;		/* hash table size */
	Node * slots;	/* array of slots */
} Hash_OA;

/* When the slot is unoccupied, the key is HASH_NULL_KEY */
#define HASH_NULL_KEY 2100


/* Hash Table Open Addressing Part */
/* Initialize the hash table to size s #1 */
/* Return a new empty hash table with size s */
void hash_init(Hash_OA **T, int s);

/* Make the hash table T empty #2 */
void hash_make_empty(Hash_OA *T);

/* Insert (key, value) to the hash table T #3 #4 */
/* If key does not exist in T, then add (key, value) to the front of the list */
/* If key already exist in T, then update the value */
/* return 1 if key is added to T successfully */
/* return 2 if key already exists in T and values is updated accordingly */
/* return 0 if key cannot be added to T */
int hash_insert(Hash_OA *T, int key, int value);

/* Check if key exist in the hash table T or not #5 */
/* If key in T, return 1 */
/* If key not in T, return 0 */
int hash_contain(Hash_OA *T, int key);

/* Find the value based on the key in the hash table T #6 */
/* If key in T, return the value */
/* If key does not exist in T, return INT_MAX */
int hash_find(Hash_OA *T, int key);

/* Free the hash table T, if T is not NULL #7 */
/* Assign NULL to T */
void hash_free(Hash_OA **T);

/* The hash function calculates the hash value #8 */
/* hash_value = key mod size */
/* key can be negative, but hash_value must be range between 0 and size - 1 */
int hash_function(int key, int size);

/* The second hash function calculates the step size if collision occurs #9 */
/* step_size = v - (key mod v), where v = size - 2 */
/* You can safely assume v > 0 (i.e. size > 2) */
int hash_function2(int key, int size);

/* The print function print the whole hash table in an output string #10 */
/* The first number is the index, number in the bracket is key, number after bracket is value */
/* If the hash table looks like */
/* 0:(69)105 */
/* 1:NULL    */
/* 2:NULL    */
/* 3:(58)104 */
/* 4:NULL    */
/* 5:NULL    */
/* 6:(49)103 */
/* 7:NULL    */
/* 8:(18)102 */
/* 9:(89)101 */
/* Then, the output string is "0:(69)105\n1:\n2:\n3:(58)104\n4:\n5:\n6:(49)103\n7:\n8:(18)102\n9:(89)101\n" */
char * hash_print(Hash_OA *T);

