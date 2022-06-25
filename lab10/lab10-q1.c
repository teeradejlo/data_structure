#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>


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

typedef struct ds {
	int size;		/* size of disjoint set */
	int *parent;	/* parent of each element */
	int *tree_size; /* size of a tree in the disjoint set */
} DS;

/* Your may reuse your lab8-q3 as the start of this problem */
/* Your code here */
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

/* Your may reuse your lab7-q2 as the start of this problem */
/* Your code here */
void ds_init(DS **S, int size){
	/* Your code here */
    DS *tmp = malloc(sizeof(DS));
    tmp->size = size;
    tmp->parent = malloc(sizeof(int) * size);
    tmp->tree_size = malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        tmp->parent[i] = i;
        tmp->tree_size[i] = 1;
    }

    *S = tmp;
}

/* Find the root of node x #3 */
/* Path compression is needed */
/* Return the root of node x */
int ds_find_set(DS *S, int x){
	/* Your code here */
    if (S->parent[x] == x) return x;

	return S->parent[x] = ds_find_set(S, S->parent[x]);
}

/* Check if x and y belong to the same set #4 */
/* Return 1 if they are belong to the same set */
/* Return 0 if they are not belong to the same set */
int ds_same_set(DS* S, int x, int y){
    /* Your code here */
    int rootx = ds_find_set(S, x);
    int rooty = ds_find_set(S, y);

    if (rootx == rooty) {
        return 1;
    } else {
        return 0;
    }
}

/* Union the set containing x and the set containing y #5 #6 */
/* Put the set containing y as the subtree of the set of containing x */
/* You need to update tree_size */
void ds_union(DS *S, int x, int y){
	/* Your code here */
	int rootx = ds_find_set(S, x);
	int rooty = ds_find_set(S, y);

    if (ds_same_set(S, x, y)) {
        return;
    } else {
        S->parent[rooty] = rootx;
        S->tree_size[rootx] += S->tree_size[rooty];
    }
}

/* Union the set containing x and the set containing y #7 #8 */
/* Put the smaller set as the subtree of the larger set */
/* If both sets have the same set, put set containing x as the subtree of set containing y */
/* Remember to update tree_size */
void ds_union_by_size(DS *S, int x, int y){
	/* Your code here */
    int rootx = ds_find_set(S, x);
	int rooty = ds_find_set(S, y);

    if (ds_same_set(S, x, y)) {
        return;
    } else {
        if (S->tree_size[rootx] > S->tree_size[rooty]) {
            S->parent[rooty] = rootx;
            S->tree_size[rootx] += S->tree_size[rooty];
        } else {
            S->parent[rootx] = rooty;
            S->tree_size[rooty] += S->tree_size[rootx];
        }
    }
}

/* Free the disjoint set #9 */
/* Assign NULL pointer to *S */
void ds_free(DS **S){
	/* Your code here */
    if (S == NULL) return;
    if (*S == NULL) return;
    free((*S)->parent);
    free((*S)->tree_size);
    free(*S);
    *S = NULL;
}


int main(int argc, char *argv[]){

	FILE *fin, *fout;
	int i, j, u, v, w, n, e, cnt;
	int total_mst;
	EdgeList *G;
	DS *S;
	Edge tmpedge;
	int minweight, minedge;

	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	fscanf(fin, "%d%d", &n, &e);

    /* Your code here */
    el_graph_init(&G, n, e);
    ds_init(&S, n);

	for (i = 0; i < e; i++) {
		fscanf(fin, "%d%d%d", &u, &v, &w);
		/* Your code here */
        tmpedge.v = u;
        tmpedge.w = v;
        tmpedge.weight = w;

        el_insert_edge(G, tmpedge);
	}

	/* Kruskal Algorithm */
	/* Your code here */
	for(i = 0; i < e; i++) {
        minedge = i;
        minweight = G->edgelist[i].weight;
        v = G->edgelist[i].v;
        w = G->edgelist[i].w;
        for (j = i+1; j < e; j++) {
            if (G->edgelist[j].weight < minweight || (G->edgelist[j].weight == minweight
                    && (G->edgelist[j].v < v || (G->edgelist[j].v == v && G->edgelist[j].w < w)))) {
                minedge = j;
                minweight = G->edgelist[j].weight;
                v = G->edgelist[j].v;
                w = G->edgelist[j].w;
            }
        }
        if (minedge != i) {
            G->edgelist[minedge].v = G->edgelist[i].v;
            G->edgelist[minedge].w = G->edgelist[i].w;
            G->edgelist[minedge].weight = G->edgelist[i].weight;

            G->edgelist[i].v = v;
            G->edgelist[i].w = w;
            G->edgelist[i].weight = minweight;
        }
	}

	for (i = 0; i < e; i++) {
    /* Your code here */
        fprintf(stdout, "%d %d %d\n", G->edgelist[i].v, G->edgelist[i].w, G->edgelist[i].weight);
    }

	cnt = 1;
	total_mst = 0;
	for (i = 0; i < e && cnt < n; i++) {
        /* Your code here */
        if(ds_same_set(S, G->edgelist[i].v, G->edgelist[i].w)) {
            fprintf(fout, "%d %d %d dropped\n", G->edgelist[i].v, G->edgelist[i].w, G->edgelist[i].weight);
            continue;
        }

		/* Output format, you need to edit statement line number and parameters */
		ds_union(S, G->edgelist[i].v, G->edgelist[i].w);
		cnt++;
		total_mst += G->edgelist[i].weight;
		fprintf(fout, "%d %d %d selected\n", G->edgelist[i].v, G->edgelist[i].w, G->edgelist[i].weight);
	}

	/* Output format */
	fprintf(fout, "The weight of the minimum spanning tree is %d.\n", total_mst);

    /* Your code here */
    el_free(&G);
    ds_free(&S);

	fclose(fin);
	fclose(fout);

	return 0;
}
