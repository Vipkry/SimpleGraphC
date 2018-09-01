#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

#define MAX_SIZE 26

/* Maps vertex char to int.
   Uppercase letters only */
int map(char c){ ;
    return (int) c - (int) 'A';
}

Graph initGraph(){
    Graph* g  = (Graph *) malloc(sizeof(Graph));
    g->matrix = (int **) malloc(sizeof(int **) * MAX_SIZE);
    g->vertexes = 0;
    g->edges = 0;
    return *g;
}

void insertVertex(Graph *g, char v){
    int vertex = map(v);
    g->matrix[vertex] = (int *) malloc(sizeof(int *) * MAX_SIZE);
    // sets initial neighbors
    for(int i = 0; i < MAX_SIZE; i++) g->matrix[vertex][i] = 0;
    g->vertexes++;
}

void insertEdge(Graph *g, char v, char u){
    int v1 = map(v), v2 = map(u);
    g->matrix[v1][v2]++;
    g->matrix[v2][v1]++;
    g->edges++;
}

void removeEdge(Graph *g, char v, char u){
    int v1 = map(v), v2 = map(u);
    g->matrix[v1][v2]--;
    g->matrix[v2][v1]--;
    g->edges--;
}

int vertexSize(Graph g){
    Graph* graph = &g;
    return graph->vertexes;
}

int edgeSize(Graph g){
    Graph* graph = &g;
    return graph->edges;
}