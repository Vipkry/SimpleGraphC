#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graphMatriz.h"

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

    // 0 -> vertex not inserted
    // 1 -> vertex inserted

    for(int i = 0; i < MAX_SIZE; i++) vertexes[i] = 0;
    return vertexes;
}

Graph initGraph(){
    Graph* g  = (Graph *) malloc(sizeof(Graph));
    g->matrix = (int **) malloc(sizeof(int *) * MAX_SIZE);
    g->vertexes = initializeVertexes();
    g->edges = 0;
    return *g;
}

void insertVertex(Graph *g, char v){
    if (hasVertex(g, v)) return defaultErrorMessage();

    int vertex = to_int(v);
    g->matrix[vertex] = (int *) malloc(sizeof(int *) * MAX_SIZE);
    for(int i = 0; i < MAX_SIZE; i++) g->matrix[vertex][i] = 0; // sets initial neighbors
    g->vertexes[vertex] = 1;
}

void insertEdge(Graph *g, char v, char u){
    if (!hasVertex(g, v) || !hasVertex(g, u)) return defaultErrorMessage();

    int v1 = to_int(v), v2 = to_int(u);
    g->matrix[v1][v2]++;
    g->matrix[v2][v1]++;
    g->edges++;
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

    int i = to_int(v), j = to_int(u);
    return graph->matrix[i][j];
}

void neighbours(Graph g, char v){
    Graph* graph = &g;
    if (!hasVertex(graph, v)) return defaultErrorMessage();

    int i, vertex = to_int(v);
    for (i = 0; i < MAX_SIZE; i++){
        if (graph->matrix[vertex][i] != 0){
            printf("%c is %c neighbour\n", to_char(i), v);
        }
    }
}

void removeEdge(Graph *g, char v, char u){
    if (!hasVertex(g, v) || !hasVertex(g, u)) return defaultErrorMessage();
    int v1 = to_int(v), v2 = to_int(u);

    if(g->matrix[v1][v2] == 0){
        printf("Skipping nonexistent edge removal\n");
        return;
    }

    g->matrix[v1][v2]--;
    g->matrix[v2][v1]--;
    g->edges--;
}

void removeVertex(Graph *g, char v){
    if (!hasVertex(g, v)) return defaultErrorMessage();
    int i, j, k, n_edges, vertex = to_int(v);

    // iterate through the entire matrix cleaning connections to the vertex we're removing
    for (i = 0; i < MAX_SIZE; i++){
        if (g->vertexes[i] != 0){ // skipping nonexistent vertexes
            for (j = 0; j < MAX_SIZE; j++){
                if (i == vertex || j == vertex){ // if it's the vertex we're trying to remove
                    n_edges = g->matrix[i][j];
                    for (k = 0; k < n_edges; k++) removeEdge(g, to_char(i), to_char(j));
                }
            }
        }
    }

    g->vertexes[vertex] = 0;
    // free the correspondent matrix array as it was removed therefore there's no edge connecting them
    free(g->matrix[vertex]);
}

void endGraph(Graph *g){
    // free the matrix
    for (int i = 0; i < MAX_SIZE; i++)
        // vertexes set to zero means they're not initialized or have already been freed
        if (g->vertexes[i] != 0)
            free(g->matrix[i]);

    free(g->matrix);
    free(g->vertexes);
}


void dijkstra(Graph *g, char s){
    if (!hasVertex(g, s)) return defaultErrorMessage();

    int vertex = to_int(s), i, j, dist_adj, x, min;

    int* dist       = (int *) malloc(sizeof(int)   * MAX_SIZE);
    int* prev       = (int *) malloc(sizeof(int *) * MAX_SIZE);
    int* verified   = (int *) malloc(sizeof(int)   * MAX_SIZE);

    for (i = 0; i < MAX_SIZE; i++)
    {
        dist[i] = INT_MAX;
        prev[i] = -1;
        verified[i] = 0;
    }

    dist[vertex] = 0;

    for (i = 0; i < MAX_SIZE; i++)
    {

        min = -1;
        for (j = 0; j < MAX_SIZE; j++)
        {
            if (g->vertexes[j] && verified[j] == 0 && (min == -1 || dist[j] < dist[min]))
                min = j;
        }

        x = min;
        if (x == -1) break;

        // for all possible adjacent vertexes
        for (j = 0; j < MAX_SIZE; j++)
        {
            dist_adj = g->matrix[x][j];
            // if it's a neighbor indeed
            // and it was not yet marked as verified[]
            // and its distance should be updated
            // != INT_MAX protection against integer overflowing
            if (dist_adj > 0 && verified[j] == 0 && dist[j] > dist[x] + dist_adj && dist[x] != INT_MAX)
            {
                dist[j] = dist[x] + dist_adj;
                prev[j] = x;
            }
        }

        verified[x] = 1;
    }

    for (i = 0; i < MAX_SIZE; i++)
    {
        if (g->vertexes[i] > 0)
        {
            char v = to_char(i);
            char pai = prev[i] == -1 ? '-' : to_char(prev[i]);
            printf("dist[%c] = %d \t\t pai[%c] = %c\n", v, dist[i], v, pai);
        }
    }

    free(dist);
    free(prev);
    free(verified);
}