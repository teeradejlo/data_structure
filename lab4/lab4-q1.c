#include"lab4-q1.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

/* Linked List Part */
/* Insert (key, value) to the front of the linked list L #10 */
/* If key does not exist in T, then add (key, value) to the front of the list */
/* If key already exist in T, then update the value */
/* Return list head */
List* list_insert(List *L, int key, int value){
	List *tmp = NULL, *ptr;
    /* Your code here */
    ptr = L;
    while (ptr != NULL) {
        if (ptr->key == key) {
            ptr->value = value;
            return L;
        }
        ptr = ptr->next;
    }

    tmp = malloc(sizeof(List));
    tmp->key = key;
    tmp->value = value;

    tmp->next = L;

	return tmp;
}

/* Delete key from the linked list L #10 */
/* If key does not exist in T, then do nothing */
/* Return the head of the list */
List* list_delete(List *L, int key){
	List *tmp = NULL, *prev = NULL;
	/* Your code here */
    tmp = L;
    while (tmp != NULL) {
        if (tmp->key == key) {
            if (prev != NULL) {
                //middle of list
                prev->next = tmp->next;
                free(tmp);
                return L;
            } else {
                L = tmp->next;
                free(tmp);
                return L;
            }
        }
        prev = tmp;
        tmp = tmp->next;
    }
    //key not exist in L
	return L;
}

/* Find the value based on the key in the L #10 */
/* If key in L, return the value */
/* If key does not exist in L, return INT_MAX */
int list_find(List *L, int key){
	/* Your code here */
	List *ptr = L;
    while (ptr != NULL) {
        if (ptr->key == key) {
            return ptr->value;
        }
        ptr = ptr->next;
    }

	return INT_MAX;
}

/* Hash Table Separate Chaining Part */
/* Initialize the hash table to size s #1 */
/* Create a new empty hash table with size s */
void hash_init(Hash_SC ** T, int s){
	/* Your code here */
    Hash_SC *tmp = malloc(sizeof(Hash_SC));
    tmp->size = s;
    tmp->slots = malloc(sizeof(List*) * s);
    for (int i = 0; i < s; i++) {
        tmp->slots[i] = NULL;
    }

    *T = tmp;
}

/* Make the hash table T empty #2 */
/* an empty linked list is pointing to NULL */
void hash_make_empty(Hash_SC *T){
	/* Your code here */
    for (int i =0; i< T->size; i++) {
        while (T->slots[i] != NULL) {
            T->slots[i] = list_delete(T->slots[i], T->slots[i]->key);
        }
    }
}

/* Insert (key, value) to the hash table T */
/* If key does not exist in T, then add (key, value) to the front of the list #3 */
/* If key already exist in T, then update the value #4 */
void hash_insert(Hash_SC *T, int key, int value){
	/* Your code here */
    int hash_code = hash_function(key, T->size);
    T->slots[hash_code] = list_insert(T->slots[hash_code], key, value);
}

/* Delete key from the hash table T #5 */
/* If key does not exist in T, then do nothing */
void hash_delete(Hash_SC *T, int key){
	/* Your code here */
    int hash_code = hash_function(key, T->size);
    T->slots[hash_code] = list_delete(T->slots[hash_code], key);
}

/* Check if key exist in the hash table T or not #6 */
/* If key in T, return 1 */
/* If key not in T, return 0 */
int hash_contain(Hash_SC *T, int key){
	/* Your code here */
    int hash_code = hash_function(key, T->size);
    int value = list_find(T->slots[hash_code], key);
    if (value == INT_MAX) {
        return 0;
    }
	return 1;
}

/* Find the value based on the key in the hash table T #7 */
/* If key in T, return the value */
/* If key does not exist in T, return INT_MAX */
int hash_find(Hash_SC *T, int key){
	/* Your code here */
    int hash_code = hash_function(key, T->size);
	return list_find(T->slots[hash_code], key);
}

/* Free the hash table T, if T is not NULL #8 */
/* Assign NULL to T */
void hash_free(Hash_SC **T){
	/* Your code here */
    int i;
    if (*T == NULL) return;
    hash_make_empty(*T);
    free((*T)->slots);
    free(*T);
    *T=NULL;
}

/* The hash function calculates the hash value #9 */
/* hash_value = key mod size */
/* key can be negative, but hash_value must be range between 0 and size - 1 */
int hash_function(int key, int size) {
    /* Your code here */
    int hash_code = key % size;
    if (hash_code >= 0) return hash_code;
    return hash_code+size;
}



