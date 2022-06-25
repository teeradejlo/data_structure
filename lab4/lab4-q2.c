#include"lab4-q2.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

/* Initialize the hash table to size s #1 */
/* Return a new empty hash table with size s */
void hash_init(Hash_OA **T, int s){
	/* Your code here */
    Hash_OA *tmp = malloc(sizeof(Hash_OA));
    memset(tmp, 0, sizeof(Hash_OA));
    tmp->size = s;
    tmp->slots = malloc(sizeof(Node) * s);
    memset(tmp->slots, 0, sizeof(Node) * s);
    hash_make_empty(tmp);
    *T = tmp;
}

/* Make the hash table T empty #2 */
void hash_make_empty(Hash_OA *T){
	/* Your code here */
	int s = T->size;
    for (int i = 0; i < s; i++) {
        T->slots[i].key = HASH_NULL_KEY;
    }
}

/* Insert (key, value) to the hash table T #3 #4 */
/* If key does not exist in T, then add (key, value) to the front of the list */
/* If key already exist in T, then update the value */
/* return 1 if key is added to T successfully */
/* return 2 if key already exists in T and values is updated accordingly */
/* return 0 if key cannot be added to T */
int hash_insert(Hash_OA *T, int key, int value){
	/* Your code here */
    int hash_val, h1, h2, count;
    h1 = hash_function(key, T->size);
    h2 = hash_function2(key, T->size);
    count = 0;

    while (count < T->size) {
        hash_val = (h1+ count * h2) % T->size;
        if (T->slots[hash_val].key == key) {
            T->slots[hash_val].value = value;
            return 2;
        }
        if (T->slots[hash_val].key == HASH_NULL_KEY) {
            T->slots[hash_val].key = key;
            T->slots[hash_val].value = value;
            return 1;
        }
        count++;
    }
    return 0;
}

/* Check if key exist in the hash table T or not #5 */
/* If key in T, return 1 */
/* If key not in T, return 0 */
int hash_contain(Hash_OA *T, int key){
	/* Your code here */
    int hash_val, h1, h2, count;

    h1 = hash_function(key, T->size);
    h2 = hash_function2(key, T->size);
    count = 0;

    do {
        hash_val = (h1 + count * h2) % T->size;
        if (T->slots[hash_val].key == key) {
            return 1;
        }
        count = count + 1;
    } while (T->slots[hash_val].key != HASH_NULL_KEY && count < T->size);

    return 0;
}

/* Find the value based on the key in the hash table T #6 */
/* If key in T, return the value */
/* If key does not exist in T, return INT_MAX */
int hash_find(Hash_OA *T, int key){
	/* Your code here */
	int h1 = hash_function(key, T->size);
	int h2 = hash_function2(key, T->size);
	int count = 0;
	int hash_code;

	do {
        hash_code = (h1 + count * h2) %T->size;
        if (T->slots[hash_code].key == key)
            return T->slots[hash_code].value;
        count++;
	} while (T->slots[hash_code].key != HASH_NULL_KEY && count < T->size);

	return INT_MAX;
}

/* Free the hash table T, if T is not NULL #7 */
/* Assign NULL to T */
void hash_free(Hash_OA **T){
	/* Your code here */
    if (*T == NULL) return;

    free((*T)->slots);
    free(*T);
    *T = NULL;

}

/* The hash function calculates the hash value #8 */
/* hash_value = key mod size */
/* key can be negative, but hash_value must be range between 0 and size - 1 */
int hash_function(int key, int size){
    /* Your code here */
	return ((key % size) + size) % size;
}

/* The second hash function calculates the step size if collision occurs #9 */
/* step_size = v - (key mod v), where v = size - 2 */
/* You can safely assume v > 0 (i.e. size > 2) */
/* key can be negative, but hash_value must be range between 1 and size - 2 */
int hash_function2(int key, int size){
	/* Your code here */
	int v = size - 2;
	return v - (((key % v) + v) % v);
}

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
char * hash_print(Hash_OA *T){
	char *output = NULL;
	/* Your code here */
    int len = 4 * T->size + 26 * T->size;
    output = malloc(sizeof(char) * len);
	memset(output, 0, sizeof(char) * len);

	for(int i = 0; i<T->size; i++) {
        sprintf(output, "%s%d:", output, i);
        if (T->slots[i].key != HASH_NULL_KEY) {
            sprintf(output, "%s(%d)%d", output, T->slots[i].key, T->slots[i].value);
        }
        sprintf(output, "%s\n", output);
	}

	return output;
}

