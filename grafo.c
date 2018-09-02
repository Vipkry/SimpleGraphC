#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

#define MAX_SIZE 26

void defaultErrorMessage(){
    printf("A vertex/edge is being used before assignment or you are trying to re-assign it.\n"
          "Are you sure you inserted/removed the vertex/edge correctly?\n");
}

/* Maps vertex char to int.
   Uppercase letters only */
int map(char c){ ;
    return (int) c - (int) 'A';
}

/* Check if vertex exists in given graph */
int hasVertex(Graph *g, char c){
    int vertex = map(c);
    return g->vertexes[vertex];
}

/* initGraph helper for initializing vertexes list */
int* initializeVertexes(){
    int* vertexes = (int *) malloc(sizeof(int *) * MAX_SIZE);

    // 0 -> vertex not inserted
    // 1 -> vertex inserted

    for(int i = 0; i < MAX_SIZE; i++) vertexes[i] = 0;
    return vertexes;
}

Graph initGraph(){
    Graph* g  = (Graph *) malloc(sizeof(Graph));
    g->matrix = (int **) malloc(sizeof(int **) * MAX_SIZE);
    g->vertexes = initializeVertexes();
    g->edges = 0;
    return *g;
}

void insertVertex(Graph *g, char v){
    if (hasVertex(g, v)) return defaultErrorMessage();

    int vertex = map(v);
    g->matrix[vertex] = (int *) malloc(sizeof(int *) * MAX_SIZE);
    for(int i = 0; i < MAX_SIZE; i++) g->matrix[vertex][i] = 0; // sets initial neighbors
    g->vertexes[vertex] = 1;
}

void insertEdge(Graph *g, char v, char u){
    if (!hasVertex(g, v) || !hasVertex(g, u)) return defaultErrorMessage();

    int v1 = map(v), v2 = map(u);
    g->matrix[v1][v2]++;
    g->matrix[v2][v1]++;
    g->edges++;
}

int vertexSize(Graph g){
    Graph* graph = &g;
    int counter = 0, i = 0;
    for(i; i < MAX_SIZE; i++)
        if (graph->vertexes[i] == 1)
            counter++;
    return counter;
}

int edgeSize(Graph g){
    Graph* graph = &g;
    return graph->edges;
}

void removeEdge(Graph *g, char v, char u){
    if (!hasVertex(g, v) || !hasVertex(g, u)) return defaultErrorMessage();
    int v1 = map(v), v2 = map(u);

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

    // remove todas arestas realcionadas ao vértice
        // percorre matriz de adjacencia procurando links do vértice
        // seta todos eles 0
        // reduz o nº de vértices pra ficar de acordo
    // remove vértice
        // tira ele da lista
        // free no vértice
}

