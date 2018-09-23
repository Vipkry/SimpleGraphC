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
        g = g->next_vertex;
    }
    return 0;
}

Graph initGraph(){
    Graph* g  = (Graph *) malloc(sizeof(Graph));
    g->vertex = '\0'; // first vertex will always be \0 for simplification purposes
    g->edges = 0;
    return *g;
}

Graph* findVertex(Graph *g, char v){
    while (g != NULL){
        if(g->vertex == v) return g;
        g = g->next_vertex;
    }

    defaultErrorMessage();
    return NULL;

}

Edge* findEdgeFromVertex(Graph *g, char v){
    Edge *edge = g->edges;
    while(edge != NULL && edge->neighbour != v) edge = edge->next_edge;
    return edge;
}

void insertVertex(Graph *g, char v){
    if (hasVertex(g, v)) return defaultErrorMessage();
    // get the latest vertex
    while (g->next_vertex != NULL) g = g->next_vertex;

    Graph *newGraph = (Graph *) malloc(sizeof(Graph));
    newGraph->vertex = v;
    newGraph->next_vertex = NULL;
    g->next_vertex = newGraph;
}

void insertEdgeToVertex(Graph *g, char new_neighbour){
    // check if edge already exists
    Edge *new_edge = findEdgeFromVertex(g, new_neighbour);

    if (new_edge != NULL){
        // if the edge already exists just increment the number of edges
        new_edge->n_edges++;
    }else {
        // crete new edge
        new_edge = (Edge *) malloc(sizeof(Edge));
        new_edge->neighbour = new_neighbour;
        new_edge->n_edges = 1;

        // find last_edge
        Edge *last_edge = g->edges;
        if (last_edge != NULL){
            while(last_edge->next_edge != NULL) last_edge = last_edge->next_edge;
            //insert new edge
            last_edge->next_edge = new_edge;
        }else {
            g->edges = new_edge;
        }

    }

}

void insertEdge(Graph *g, char v, char u){
    // locate v vertex
    Graph *v_vertex = findVertex(g, v);
    // locate u vertex
    Graph *u_vertex = findVertex(g, u);

    if (u_vertex == NULL || v_vertex == NULL) return;

    // in case we want directional edges representations, just change lines below.
    // insert edge connecting v -> u
    insertEdgeToVertex(v_vertex, u);
//     insert edge connecting u -> v
    insertEdgeToVertex(u_vertex, v);

    g->total_edges += 2;
}

int vertexSize(Graph g){
    Graph* graph = &g;
    int i;
    for(i = -1; graph != NULL; graph = graph->next_vertex, i++);
    return i;
}

int edgeSize(Graph g){
    Graph* graph = &g;
    // return graph->edges in case of directional edges
    return graph->total_edges / 2;
}

int isNeighbour(Graph g, char v, char u){
    // locate v vertex
    Graph *v_vertex = findVertex(&g, v);
    // locate u vertex
    Graph *u_vertex = findVertex(&g, u);

    if (u_vertex == NULL || v_vertex == NULL) return 0;

    Edge *edge = findEdgeFromVertex(v_vertex, u);

    return edge != NULL ? 1 : 0;
}

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
        g = g->next_vertex;
    }

    // remove and free the correspondent edges of the removed vertex
    // removeEdges(g);

    // with all edges removed we're safe to remove and free the given vertex
    previous->next_vertex = g->next_vertex;
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