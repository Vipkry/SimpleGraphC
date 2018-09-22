#include <stdio.h>
#include <stdlib.h>
#include "graphLista.h"

/* Displays error message in case the program is trying to access or make use of
 * vertexes not yet initialized or re-assigning one of them */
void defaultErrorMessage(){
    printf("A vertex/edge is being used before assignment or you are trying to re-assign it.\n"
          "Are you sure you inserted/removed the vertex/edge correctly?\n");
}

/* Check if vertex exists in given graph */
int hasVertex(Graph *g, char c){
    while(g != NULL){
        if (g->vertex == c) return 1;
        g = g->next;
    }
    return 0;
}

Graph initGraph(){
    Graph* g  = (Graph *) malloc(sizeof(Graph));
    g->vertex = '\0'; // first vertex will always be \0 for simplification purposes
    return *g;
}

void insertVertex(Graph *g, char v){
    if (hasVertex(g, v)) return defaultErrorMessage();
    // get the latest vertex
    while (g->next != NULL) g = g->next;

    Graph *newGraph = (Graph *) malloc(sizeof(Graph));
    newGraph->vertex = v;
    g->next = newGraph;
}

//void insertEdge(Graph *g, char v, char u){
//    if (!hasVertex(g, v) || !hasVertex(g, u)) return defaultErrorMessage();
//
//    int v1 = to_int(v), v2 = to_int(u);
//    g->matrix[v1][v2]++;
//    g->matrix[v2][v1]++;
//    g->edges++;
//}
//
int vertexSize(Graph g){
    Graph* graph = &g;
    int i;
    for(i = -1; graph != NULL; graph = graph->next, i++);
    return i;
}
//
//int edgeSize(Graph g){
//    Graph* graph = &g;
//    return graph->edges;
//}
//
//int isNeighbour(Graph g, char v, char u){
//    Graph* graph = &g;
//
//    if (!hasVertex(graph, v) || !hasVertex(graph, u)){
//        defaultErrorMessage();
//        return 0;
//    }
//
//    int i = to_int(v), j = to_int(u);
//    return graph->matrix[i][j];
//}
//
//void neighbours(Graph g, char v){
//    Graph* graph = &g;
//    if (!hasVertex(graph, v)) return defaultErrorMessage();
//
//    int i, vertex = to_int(v);
//    for (i = 0; i < MAX_SIZE; i++){
//        if (graph->matrix[vertex][i] != 0){
//            printf("%c is %c neighbour\n", to_char(i), v);
//        }
//    }
//}
//
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

void removeVertex(Graph *g, char v){
    if (!hasVertex(g, v)) return defaultErrorMessage();

    // find the vertex
    Graph *previous = g;
    while(1){
        if (g->vertex == v) break;
        previous = g;
        g = g->next;
    }

    // remove and free the correspondent edges of the removed vertex
    // removeEdges(g);

    // with all edges removed we're safe to remove and free the given vertex
    previous->next = g->next;
    free(g);

}

//void endGraph(Graph *g){
//    // free the matrix
//    for (int i = 0; i < MAX_SIZE; i++)
//        // vertexes set to zero means they're not initialized or have already been freed
//        if (g->vertexes[i] != 0)
//            free(g->matrix[i]);
//
//    free(g->matrix);
//    free(g->vertexes);
//}