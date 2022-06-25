/* lab6-q1.h */
/* Cannot modify this file */
typedef struct bst {
    int key, value; /* key and value of the node */ 
    struct bst *lchild, *rchild; /* the two children ptr of the node */
}BST;

/* Init an empty BST #1 */
void bst_init(BST **T);

/* Create a new node with specified values #2 */
/* Set the children to NULL */
BST* bst_create_node(int key, int value);

/* Search for key in the tree #3 */
/* Return the node with the key */
/* Return NULL if the key does not exist in the tree  */
BST *bst_find(BST *T, int key); 

/* Insert the (key,value) pair into the tree #4 #5 */
/* If key exist in the tree, update the value */
/* If key does not exist in the tree, create the new node and add to the tree */
/* Return the root of the tree */
BST* bst_insert(BST *T, int key, int value);
	
/* Delete the node with specified key #6 #7 #8 */
/* If key does not exist in the tree, do nothing */
/* If key is leaf, delete it directly */
/* If key has one child, adjust a pointer to bypass this node and delete it */
/* If key has two children, replace the (key,value) of this node with the largest (key,value) of the left subtree, and propagate the deletion */
/* Return the root of the tree */
BST *bst_delete(BST *T, int key);

/* Find the node storing maximum key among all nodes in the tree #9 */
BST *bst_find_max(BST *T);

/* Free the tree #10 */
/* Assign NULL pointer to *T */
void bst_free(BST **T);


