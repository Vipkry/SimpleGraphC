#include <stdio.h>
#include <stdlib.h>
#include "graphIncid.h"

/* Displays error message in case the program is trying to access or make use of
 * vertexes not yet initialized or re-assigning one of them */
void defaultErrorMessage(){
    printf("A vertex/edge is being used before assignment or you are trying to re-assign it.\n"
          "Are you sure you inserted/removed the vertex/edge correctly?\n");
}

/* Maps vertex char to int.
*  Uppercase letters only */
int to_int(char c){ ;
    return (int) c - (int) 'A';
}

/* Maps vertex int to char.
*  starting by uppercase 'A' */
char to_char(int i){
    return i + 'A';
}

/* Check if vertex exists in given graph */
int hasVertex(Graph *g, char c){
    int vertex = to_int(c);
    return g->vertexes[vertex];
}

/* initGraph helper for initializing vertexes list */
int* initializeVertexes(){
    int* vertexes = (int *) malloc(sizeof(int) * MAX_ROW_SIZE);

//     0 -> vertex not inserted
//     1 -> vertex inserted
//
    for(int i = 0; i < MAX_ROW_SIZE; i++) vertexes[i] = 0;
    return vertexes;
}

Graph initGraph(){
    Graph* g = (Graph *) malloc(sizeof(Graph));
    g->vertexes = initializeVertexes();
    g->edges = 0;
    return *g;
}

void insertVertex(Graph *g, char v){
    if (hasVertex(g, v)) return defaultErrorMessage();
    int vertex = to_int(v);
    g->vertexes[vertex] = 1;
}

void insertEdge(Graph *g, char v, char u){
    if (!hasVertex(g, v) || !hasVertex(g, u)) return defaultErrorMessage();

    int v1 = to_int(v), v2 = to_int(u);
    g->edges++;
    // we could search for an existing edge before inserting, but that would increase our complexity to O(n)
    // while not searching for it has O(4) dismissing realloc complexity.
    g->matrix = (int **) realloc(g->matrix, g->edges * sizeof(int *));
    int last_edge_index = g->edges - 1;
    g->matrix[g->edges - 1] = (int *) malloc(sizeof(int) * MAX_ROW_SIZE);
    g->matrix[last_edge_index][v1] = 0;
    g->matrix[last_edge_index][v2] = 0;
    g->matrix[last_edge_index][v1]++;
    g->matrix[last_edge_index][v2]++;
}

int vertexSize(Graph g){
    Graph* graph = &g;
    int counter = 0, i = 0;
    // vertexes set to one means they have been initialized, therefore are part of the graph
    for(i; i < MAX_ROW_SIZE; i++)
        if (graph->vertexes[i] == 1)
            counter++;
    return counter;
}

int edgeSize(Graph g){
    Graph* graph = &g;
    return graph->edges;
}

int isNeighbour(Graph g, char v, char u){
    Graph* graph = &g;

    if (!hasVertex(graph, v) || !hasVertex(graph, u)){
        defaultErrorMessage();
        return 0;
    }

    int i, j, v1 = to_int(v), v2 = to_int(u);

    // for each edge
    for (i = 0; i < graph->edges; i++){
        // if that edge reaches a given vertex
        if (graph->matrix[i][v1]){
            // search for it's neighbours and check if it's a match
            for(j = 0; j < MAX_ROW_SIZE; j++){
                if (graph->matrix[i][j] && j == v2){
                    return 1;
                }
            }
        }
    }

    return 0;

}

void neighbours(Graph g, char v){
    Graph* graph = &g;

    if (!hasVertex(graph, v)) return defaultErrorMessage();

    int i, j, vertex = to_int(v);

    // for each edge
    for (i = 0; i < graph->edges; i++){
        // if that edge reaches the given vertex
        if (graph->matrix[i][vertex]){
            // search for it's neighbour
            for(j = 0; j < MAX_ROW_SIZE; j++){
                if (graph->matrix[i][j] && j != vertex){
                    printf("%c is %c neighbour\n", to_char(j), v);
                }
            }
        }
    }
}

void removeEdge(Graph *g, char v, char u){
    if (!hasVertex(g, v) || !hasVertex(g, u)) return defaultErrorMessage();
    int v1 = to_int(v), v2 = to_int(u), i = 0, j = 0;

    int edge_row_index = -1;
    for (i = 0; i < g->edges; i++){
        if (g->matrix[i][v1] > 0 && g->matrix[i][v2] > 0){
            edge_row_index = i;
            break;
        }
    }

    if (edge_row_index == -1){
        printf("Skipping a non-existing edge removal %c -> %c\n", v, u);
        return;
    }

    // copy rows one index backwards to remove the given edge
    for (i = edge_row_index + 1; i < g->edges; i++)
        for (j = 0; j < MAX_ROW_SIZE; j++)
            g->matrix[i - 1][j] = g->matrix[i][j];

    g->edges--;
    g->matrix = (int **) realloc(g->matrix, g->edges * sizeof(int *));
}

void removeEdgeByIndex(Graph *g, int index, int vertex){
    for (int i = 0; i < MAX_ROW_SIZE; i++){
        // hits the other side oof the edge
        // == 2 in case of loops
        if ((i != vertex && g->matrix[index][i] > 0) || g->matrix[index][i] == 2){
            removeEdge(g, to_char(vertex), to_char(i));
            return;
        }
    }

}

void removeVertex(Graph *g, char v) {
    if (!hasVertex(g, v)) return defaultErrorMessage();
    int vertex = to_int(v), i, aux = 1;

    // remove all edges related to the given vertex
    while(aux == 1) {
        aux = 0;
        for (i = 0; i < g->edges; i++) {
            if (g->matrix[i][vertex] > 0) {
                removeEdgeByIndex(g, i, vertex);
                aux = 1;
                break;
            }
        }
    }

    g->vertexes[vertex] = 0;

}

//void endGraph(Graph *g){
    // free the matrix
//    for (int i = 0; i < MAX_ROW_SIZE; i++)
        // vertexes set to zero means they're not initialized or have already been freed
//        if (g->vertexes[i] != 0)
//            free(g->matrix[i]);
//
//    free(g->matrix);
//    free(g->vertexes);
//}