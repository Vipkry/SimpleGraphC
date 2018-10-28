#include <stdio.h>
#include <stdlib.h>
#include "graphIncid.h"

/* There are 26 uppercase letters available in ASCII table
*  as they're going to be used as vertexes indexes, we can restrict
*  the maximum number of vertexes as 26 */
#define MAX_SIZE 26

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
    int* vertexes = (int *) malloc(sizeof(int) * MAX_SIZE);

//     0 -> vertex not inserted
//     1 -> vertex inserted
//
    for(int i = 0; i < MAX_SIZE; i++) vertexes[i] = 0;
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
    g->matrix = (int **) realloc(g->matrix, g->edges);
    g->matrix[g->edges - 1] = (int *) malloc(sizeof(int) * MAX_SIZE);
    g->matrix[g->edges - 1][v1] = 1;
    g->matrix[g->edges - 1][v2] = 1;
}

int vertexSize(Graph g){
    Graph* graph = &g;
    int counter = 0, i = 0;
    // vertexes set to one means they have been initialized, therefore are part of the graph
    for(i; i < MAX_SIZE; i++)
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
            for(j = 0; j < MAX_SIZE; j++){
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
            for(j = 0; j < MAX_SIZE; j++){
                if (graph->matrix[i][j] && j != vertex){
                    printf("%c is %c neighbour\n", to_char(j), v);
                }
            }
        }
    }
}

//void removeEdge(Graph *g, char v, char u){
//    if (!hasVertex(g, v) || !hasVertex(g, u)) return defaultErrorMessage();
//    int v1 = to_int(v), v2 = to_int(u);
//
//    if(g->matrix[v1][v2] == 0){
//        printf("Skipping nonexistent edge removal\n");
//        return;
//    }
//
//    g->matrix[v1][v2]--;
//    g->matrix[v2][v1]--;
//    g->edges--;
//}

//void removeVertex(Graph *g, char v){
//    if (!hasVertex(g, v)) return defaultErrorMessage();
//    int i, j, k, n_edges, vertex = to_int(v);
//
//     iterate through the entire matrix cleaning connections to the vertex we're removing
//    for (i = 0; i < MAX_SIZE; i++){
//        if (g->vertexes[i] != 0){ // skipping nonexistent vertexes
//            for (j = 0; j < MAX_SIZE; j++){
//                if (i == vertex || j == vertex){ // if it's the vertex we're trying to remove
//                    n_edges = g->matrix[i][j];
//                    for (k = 0; k < n_edges; k++) removeEdge(g, to_char(i), to_char(j));
//                }
//            }
//        }
//    }

//    g->vertexes[vertex] = 0;
    // free the correspondent matrix array as it was removed therefore there's no edge connecting them
//    free(g->matrix[vertex]);
//}

//void endGraph(Graph *g){
    // free the matrix
//    for (int i = 0; i < MAX_SIZE; i++)
        // vertexes set to zero means they're not initialized or have already been freed
//        if (g->vertexes[i] != 0)
//            free(g->matrix[i]);
//
//    free(g->matrix);
//    free(g->vertexes);
//}