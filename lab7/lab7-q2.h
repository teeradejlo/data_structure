/* lab7-q2.h */
/* Cannot modify this file */
typedef struct ds {
	int size;		/* size of disjoint set */
	int *parent;	/* parent of each element */
	int *tree_size; /* size of a tree in the disjoint set */
} DS;


/* Init a disjoint set with a given size  #1 #2 */
/* All node should point to itself */
void ds_init(DS **S, int size);

/* Find the root of node x #3 */
/* Path compression is needed */
/* Return the root of node x */
int ds_find_set(DS *S, int x); 

/* Check if x and y belong to the same set #4 */
/* Return 1 if they are belong to the same set */
/* Return 0 if they are not belong to the same set */
int ds_same_set(DS* S, int x, int y);

/* Union the set containing x and the set containing y #5 #6 */
/* Put the set containing y as the subtree of the set of containing x */
/* If both sets have the same set, put set containing y as the subtree of set containing x */
/* You need to update tree_size */
void ds_union(DS *S, int x, int y);
	
/* Union the set containing x and the set containing y #7 #8 */
/* Put the smaller set as the subtree of the larger set */
/* Remember to update tree_size */
void ds_union_by_size(DS *S, int x, int y);

/* Free the disjoint set #9 */
/* Assign NULL pointer to *S */
void ds_free(DS **S);

