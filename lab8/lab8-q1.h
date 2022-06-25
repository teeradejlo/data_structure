/* lab8-q1.h */
/* Cannot modify this file */
/* This is a directed, unweighted and non-simple graph */
typedef struct node_s{
    int v;
    struct node_s *next;
}Node;

typedef struct graph_t{ 
    int V; /* number of vertex */
    int E; /* number of edge */
    Node **adj; /* V linked list */
}AdjList;

typedef struct edge_t{
    int v;
    int w;
} Edge;

/* Create an adjacency list with V empty linked lists #1 */
void al_graph_init(AdjList **G, int V);

/* Insert edge e to G #2 #3 */
/* Edge e is inserted at the front of the linked list */
void al_insert_edge(AdjList *G, Edge e);

/* Remove edge e from G #4 #5 */
/* If e does not in G, do nothing */
/* If there are multiple e in G, only remove the first e */
void al_remove_edge(AdjList *G, Edge e);
	
/* Search edge e in G #6 #7 */
/* Return the number of occurence of e in G */
int al_find_edge(AdjList *G, Edge e);

/* Return the neighbours of vectex v in G #8 */
/* The return-type is linked list */
Node *al_neighbors(AdjList *G, int v);

/* Free the adjacency list #9 */
/* Assign NULL pointer to *G */
void al_free(AdjList **G);


