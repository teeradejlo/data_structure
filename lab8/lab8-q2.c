#include"lab8-q2.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

/* Create an VxV adjacency matrix #1 */
/* initial value is 0 */
void am_graph_init(AdjMatrix **G, int V){
	/* Your code here */
    AdjMatrix *tmp = malloc(sizeof(AdjMatrix));
    tmp->V = V;
    tmp->E = 0;
    tmp->adj = malloc(sizeof(int*) * V);
    for (int i = 0; i < V; i++) {
        tmp->adj[i] = malloc(sizeof(int) * V);
        for (int j = 0; j < V; j++) {
            tmp->adj[i][j] = 0;
        }
    }
    *G = tmp;
}

/* Insert edge e to G #2 */
/* Update the adjacency matrix according to the value of e */
void am_insert_edge(AdjMatrix *G, Edge e){
	/* Your code here */
	if (e.v >= G->V || e.w >= G->V) return;
	if (e.v < 0 || e.w < 0) return;

    if (G->adj[e.v][e.w] == 0) G->E++;

    G->adj[e.v][e.w] = e.weight;

}

/* Remove edge e from G #3 */
/* Set the entry to 0 */
/* You also need to check e.weight */
void am_remove_edge(AdjMatrix *G, Edge e){
	/* Your code here */
	if (e.v >= G->V || e.w >= G->V) return;
	if (e.v < 0 || e.w < 0) return;

    if (G->adj[e.v][e.w] != 0 && G->adj[e.v][e.w] == e.weight) {
        G->adj[e.v][e.w] = 0;
        G->E--;
    }
}

/* Search edge e in G #4 */
/* Return the weight of e in G */
/* Note: e.weight means nothing in this find function */
int am_find_edge(AdjMatrix *G, Edge e){
	/* Your code here */

	return G->adj[e.v][e.w];
}

/* Return the neighbors of vectex v in G #5 */
/* The return-type is an integer array */
/* index = 0 means the number of neighbors of v */
/* Suppose n neighbors are found, index = 1..n corresponds to the n neighbors */
/* The neighbors are stored in the increasing numeric order */
/* Note: weight means nothing in this neighbors function */
int *am_neighbors(AdjMatrix *G, int v){
	/* Your code here */
	int num_neighbor = 0;
	for (int i = 0; i < G->V; i++) {
        if (G->adj[v][i] != 0) {
            num_neighbor++;
        }
	}

	int* tmp = malloc(sizeof(int) * (num_neighbor + 1));
	for (int i = 0; i < num_neighbor + 1; i++) {
        tmp[i] = 0;
	}

	int tmp_index = 1;
	tmp[0] = num_neighbor;
	for (int i = 0; i < G->V; i++) {
        if (G->adj[v][i] != 0) {
            tmp[tmp_index] = i;
            tmp_index++;
        }
	}

	return tmp;
}

/* Free the adjacency matrix #6 */
/* Assign NULL pointer to *G */
void am_free(AdjMatrix **G){
	/* Your code here */
    if (G == NULL) return;
    if (*G == NULL) return;

    for (int i = 0; i < (*G)->V; i++) {
        free((*G)->adj[i]);
    }
    free((*G)->adj);
    free(*G);
    *G = NULL;
}




