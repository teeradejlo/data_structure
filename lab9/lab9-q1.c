#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

/* This is a directed, WEIGHT and non-simple graph */
typedef struct node_s{
    int v;
	int weight; /* new item */
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
	int weight; /* new item */
} Edge;

/* Your code here */
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

Node *list_insert(Node* listhead, int v, int weight) {
    Node *tmp = malloc(sizeof(Node));
    tmp->v = v;
    tmp->weight = weight;
    tmp->next = listhead;
    return tmp;
}

/* Insert edge e to G */
/* Edge e is inserted at the front of the linked list #2 #3 */
void al_insert_edge(AdjList *G, Edge e){
	/* Your code here */
	//non-simple graph no need for cheking
    G->adj[e.v] = list_insert(G->adj[e.v], e.w, e.weight);
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

int main(int argc, char *argv[]) {

	FILE * fin, * fout;
	AdjList * G;
	Edge tmpedge;
	int i, j;
	int n;
	int u, v, w;
	int *distance, *previous, *visited;
	int minvalue, minpos;
	Node * tmplist, *ptr;

	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	fscanf(fin, "%d", &n);

	/* It is a good habit to initialize the variables before use */
	al_graph_init(&G, n);
	distance = malloc(sizeof(int)*n);
	previous = malloc(sizeof(int)*n);
	visited = malloc(sizeof(int)*n);
	memset(distance, 0, sizeof(int)*n);
	memset(previous, 0, sizeof(int)*n);
	memset(visited, 0, sizeof(int)*n);

	/* Reading input */
	for (u = 0; u < n; u++) {
		v = 0;
		w = 0;
		while (fscanf(fin, "%d%d", &v, &w), v != -1 || w != -1) {

			/* Your code here */
			tmpedge.v = u;
			tmpedge.w = v;
			tmpedge.weight = w;
            al_insert_edge(G, tmpedge);
		}
	}

	/* Dijkstra initialization */
	/* Your code here */
	for (i = 0; i<n; i++) {
        previous[i] = -1;
        distance[i] = INT_MAX;
	}
    distance[0] = 0;

	/* modified Dijkstra */
	for (i = 0; i < n; i++) {

		/* Output format */
		for (j = 0; j < n-1; j++) {
			fprintf(fout, "%d ", distance[j]);
		}
		fprintf(fout, "%d\n", distance[n-1]);

		/* Your code here */
		/* find node for next iteration */
		/* Linear Search */
        v = INT_MAX;
        u = -1;
        for (j = 0; j<n; j++) {
            if(visited[j] != 0) {
                continue;
            }
            if(v > distance[j]) {
                u = j;
                v = distance[j];
            }
        }

        if(u == -1) {
            break;
        }
        visited[u] = 1;
        ptr = al_neighbors(G, u);
        /* Relaxation */
        while (ptr != NULL) {
            if (distance[ptr->v] > distance[u] + ptr->weight) {
                distance[ptr->v] = distance[u] + ptr->weight;
                previous[ptr->v] = u;
            }
            ptr = ptr->next;
        }
	}

	al_free(&G);
	free(distance);
	free(previous);
	free(visited);
	fclose(fin);
	fclose(fout);

	return 0;
}
