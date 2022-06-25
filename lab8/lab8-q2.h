/* lab8-q2.h */
/* Cannot modify this file */
/* This is a directed, weighted and simple graph */
typedef struct graph_t{ 
    int V; /* number of vertex */
    int E; /* number of edge */
    int **adj; /* V x V adjacency matrix */
}AdjMatrix;

typedef struct edge_t{
    int v;
    int w;
    int weight;
} Edge;

/* Create an VxV adjacency matrix #1 */
/* initial value is 0 */
void am_graph_init(AdjMatrix **G, int V);

/* Insert edge e to G #2 */
/* Update the adjacency matrix according to the value of e */
void am_insert_edge(AdjMatrix *G, Edge e);

/* Remove edge e from G #3 */
/* Set the entry to 0 */
/* You also need to check e.weight */
void am_remove_edge(AdjMatrix *G, Edge e);
	
/* Search edge e in G #4 */
/* Return the weight of e in G */
/* Note: e.weight means nothing in this find function */
int am_find_edge(AdjMatrix *G, Edge e);

/* Return the neighbors of vectex v in G #5 */
/* The return-type is an integer array */
/* index = 0 means the number of neighbors of v */
/* Suppose n neighbors are found, index = 1..n corresponds to the n neighbors */
/* The neighbors are stored in the increasing numeric order */
/* Note: weight means nothing in this neighbors function */
int *am_neighbors(AdjMatrix *G, int v);

/* Free the adjacency matrix #6 */
/* Assign NULL pointer to *G */
void am_free(AdjMatrix **G);


