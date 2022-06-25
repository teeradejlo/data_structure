/* lab8-q3.h */
/* Cannot modify this file */
/* This is an undirected, weighted and simple graph */
typedef struct edge_t{
    int v;
    int w;
	int weight;
} Edge;

typedef struct graph_t{ 
    int V; /* number of vertex */
    int E; /* number of edge */
	int Emax; /* max number of edge */
    Edge *edgelist; /* array of edge */
	int *vertexvalue; /* array of value of vertex */
}EdgeList;

/* Create an empty edge list with at most V vectice and Emax edges #1 #2 */
/* All entries in G->edgelist and G->vertexvalue are init as 0 */
void el_graph_init(EdgeList **G, int V, int Emax);

/* Insert edge e to G #3 */
/* If e already exsit in G, update the weight */
/* If e not in G, edge e is inserted to the last entry of the edgelist */
/* When you insert new edge ex to edgelist, make sure ex.v < ex.w */
void el_insert_edge(EdgeList *G, Edge e);

/* Remove edge e from G #4 */
/* You need to check all three entries of e */
/* If e does not in G, do nothing */
/* If e exist in G, replace current slot by the last edge in the edgelist */
void el_remove_edge(EdgeList *G, Edge e);
	
/* Search edge e in G #5 */
/* Return the weight of e in G */
/* Note: e.weight is don't care in this function */
int el_find_edge(EdgeList *G, Edge e);

/* Set the value of vectex v #6 */
void el_set_vertex_value(EdgeList *G, int v, int value);

/* Return the value of vectex v #7 */
int el_get_vertex_value(EdgeList *G, int v);

/* Free the edge list #8 */
/* Assign NULL pointer to *G */
void el_free(EdgeList **G);


