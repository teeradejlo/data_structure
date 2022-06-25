#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

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

/* Your may reuse your lab8-q2 as the start of this problem */
/* Your code here */
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


int main(int argc, char *argv[]){

	FILE *fin, *fout;
	int i, j, k, n, tmpvalue = 0;
	int contain_cycle = 0;

	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	fscanf(fin, "%d", &n);
	/* Your code here */
    AdjMatrix *G;
    Edge tmpedge;
    am_graph_init(&G, n);

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			fscanf(fin, "%d", &tmpvalue);
			/* Your code here */
            tmpedge.v = i;
            tmpedge.w = j;
            tmpedge.weight = tmpvalue;

            am_insert_edge(G, tmpedge);
		}
	}

	/* All Pairs Shortest Path Algorithm */
	/* Your code here */
	for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                if (G->adj[j][i] != INT_MAX && G->adj[i][k] != INT_MAX) {
                    if (G->adj[j][k] > G->adj[j][i] + G->adj[i][k]) {
                        G->adj[j][k] = G->adj[j][i] + G->adj[i][k];
                    }
                }
            }
        }
    }

	/* Output format, you need to edit some variables */
	for (i = 0; i < n; i++) {
		for (j = 0; j < n-1; j++) {
			fprintf(fout, "%d ", G->adj[i][j]);
		}
		fprintf(fout, "%d\n", G->adj[i][j]);
	}

	contain_cycle = 0;
	/* To detect the graph contains negative cycle or not */
	/* Your code here */
    for (i = 0; i < n && !contain_cycle; i++) {
        for (j = 0; j < n && !contain_cycle; j++) {
            for (k = 0; k < n && !contain_cycle; k++) {
                if (G->adj[j][i] != INT_MAX && G->adj[i][k] != INT_MAX) {
                    if (G->adj[j][k] > G->adj[j][i] + G->adj[i][k]) {
                        contain_cycle = 1;
                        continue;
                    }
                }
            }
        }
    }


	/* Output format */
	if (contain_cycle) {
		fprintf(fout, "The graph contains negative cycles.\n");
	} else {
		fprintf(fout, "The graph does not contain negative cycles.\n");
	}

	fclose(fin);
	fclose(fout);

	return 0;
}
