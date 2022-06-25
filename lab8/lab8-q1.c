#include"lab8-q1.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

/* Create an adjacency list with V empty linked lists #1 */
void al_graph_init(AdjList **G, int V){
	/* Your code here */
    AdjList *tmp = malloc(sizeof(AdjList));
    tmp->V = V;
    tmp->E = 0;
    tmp->adj = malloc(V * sizeof(Node*));
    for (int i = 0; i < V; i++) {
        tmp->adj[i] = NULL;
    }
    *G = tmp;
}

Node *list_insert(Node* listhead, int v) {
    Node *tmp = malloc(sizeof(Node));
    tmp->v = v;
    tmp->next = listhead;
    return tmp;
}

/* Insert edge e to G */
/* Edge e is inserted at the front of the linked list #2 #3 */
void al_insert_edge(AdjList *G, Edge e){
	/* Your code here */
	//non-simple graph no need for cheking
    G->adj[e.v] = list_insert(G->adj[e.v], e.w);
    G->E++;
}

int list_contain(Node* listhead, int v) {
    Node *tmp = listhead;
    while(tmp != NULL) {
        if(tmp->v == v) return 1;
        tmp = tmp->next;
    }
    return 0;
}

Node* list_remove(Node* listhead, int v) {
    Node *tmp = listhead, *prev = NULL;
    while(tmp != NULL) {
        if(tmp->v == v) {
            if (prev == NULL) {
                listhead = listhead->next;
            } else {
                prev->next = tmp->next;
            }
            free(tmp);
            return listhead;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

/* Remove edge e from G #4 #5 */
/* If e does not in G, do nothing */
/* If there are multiple e in G, only remove the first e */
void al_remove_edge(AdjList *G, Edge e){
	/* Your code here */
	if (list_contain(G->adj[e.v], e.w)) {
        G->adj[e.v] = list_remove(G->adj[e.v], e.w);
        G->E--;
	}
}

/* Search edge e in G #6 #7 */
/* Return the number of occurence of e in G */
int al_find_edge(AdjList *G, Edge e){
	/* Your code here */
    Node *tmp = G->adj[e.v];
    int ans = 0;
    while (tmp != NULL) {
        if (tmp->v == e.w) ans++;
        tmp = tmp->next;
    }
	return ans;
}

/* Return the neighbours of vectex v in G #8 */
/* The return-type is linked list */
Node *al_neighbors(AdjList *G, int v){
    /* Your code here */

	return G->adj[v];
}

void list_free(Node ** list) {
    if (list == NULL) return;
    if (*list == NULL) return;
    list_free(&((*list)->next));
    free(*list);
    *list = NULL;
}

/* Free the adjacency list #9 */
/* Assign NULL pointer to *G */
void al_free(AdjList **G){
	/* Your code here */
    int i;
    if (G == NULL) return;
    if (*G == NULL) return;
    for (i = 0; i<(*G)->V; i++) {
        list_free(&((*G)->adj[i]));
    }
    free(*G);
    *G = NULL;
}

