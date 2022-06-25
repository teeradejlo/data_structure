#include"lab8-q3.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

/* Create an empty edge list with at most V vectice and Emax edges #1 #2 */
/* All entries in G->edgelist and G->vertexvalue are init as 0 */
void el_graph_init(EdgeList **G, int V, int Emax){
	/* Your code here */
    EdgeList *tmp = malloc(sizeof(EdgeList));
    tmp->V = V;
    tmp->Emax = Emax;
    tmp->E = 0;
    tmp->edgelist = malloc(sizeof(Edge) * Emax);
    tmp->vertexvalue = malloc(sizeof(int) * V);
    for (int i = 0; i < Emax; i++) {
        tmp->edgelist[i].v = 0;
        tmp->edgelist[i].w = 0;
        tmp->edgelist[i].weight = 0;
    }
    for (int i = 0; i < V; i++) {
        tmp->vertexvalue[i] = 0;
    }
    *G = tmp;
}

/* Insert edge e to G #3 */
/* If e already exsit in G, update the weight */
/* If e not in G, edge e is inserted to the last entry of the edgelist */
/* When you insert new edge ex to edgelist, make sure ex.v < ex.w */
void el_insert_edge(EdgeList *G, Edge e){
	/* Your code here */
	if (e.weight == 0) return;

	//make e.v < e.w
	if (e.v > e.w) {
        int tmp = e.v;
        e.v = e.w;
        e.w = tmp;
	}

	int i;
    for (i = 0; i < G->E; i++) {
        if (G->edgelist[i].v == e.v && G->edgelist[i].w == e.w) {
            //update
            G->edgelist[i].weight = e.weight;
            return;
        }
    }

    //full
    if (G->E == G->Emax) return;

    //Insert
    G->edgelist[G->E].v = e.v;
    G->edgelist[G->E].w = e.w;
    G->edgelist[G->E].weight = e.weight;
    G->E++;
}

/* Remove edge e from G #4 */
/* You need to check all three entries of e */
/* If e does not in G, do nothing */
/* If e exist in G, replace current slot by the last edge in the edgelist */
void el_remove_edge(EdgeList *G, Edge e){
	/* Your code here */

	if (e.weight == 0) return;

	if (e.v > e.w) {
        int tmp = e.v;
        e.v = e.w;
        e.w = tmp;
	}

    for (int i = 0; i < G->E; i++) {
        if (G->edgelist[i].v == e.v && G->edgelist[i].w == e.w && G->edgelist[i].weight == e.weight) {
            G->E--;
            G->edgelist[i].v = G->edgelist[G->E].v;
            G->edgelist[i].w = G->edgelist[G->E].w;
            G->edgelist[i].weight = G->edgelist[G->E].weight;

            return;
        }
    }
}

/* Search edge e in G #5 */
/* Return the weight of e in G */
/* Note: e.weight is don't care in this function */
int el_find_edge(EdgeList *G, Edge e){
	/* Your code here */
	if (e.v > e.w) {
        int tmp = e.v;
        e.v = e.w;
        e.w = tmp;
	}

    for (int i = 0; i < G->E; i++) {
        if (G->edgelist[i].v == e.v && G->edgelist[i].w == e.w) {
            return G->edgelist[i].weight;
        }
    }

	return 0;
}

/* Set the value of vectex v #6 */
void el_set_vertex_value(EdgeList *G, int v, int value){
	/* Your code here */
    G->vertexvalue[v] = value;
}

/* Return the value of vectex v #7 */
int el_get_vertex_value(EdgeList *G, int v){
    /* Your code here */

	return G->vertexvalue[v];
}

/* Free the edge list #8 */
/* Assign NULL pointer to *G */
void el_free(EdgeList **G){
	/* Your code here */
    if (G == NULL) return;
    if (*G == NULL) return;

    free((*G)->edgelist);
    free((*G)->vertexvalue);
    free(*G);
    *G = NULL;
}

