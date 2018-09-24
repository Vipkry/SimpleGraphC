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
    g->edges = NULL;
    g->next_vertex = NULL;
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
        new_edge->next_edge = NULL;

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

    // insert edge connecting v -> u
    insertEdgeToVertex(v_vertex, u);

    // insert edge connecting u -> v
    // unless in case of u == v, we would be inserting duplicates otherwise
    if (u != v) insertEdgeToVertex(u_vertex, v);

    g->total_edges++;
}

int vertexSize(Graph g){
    Graph* graph = &g;
    int i;
    for(i = -1; graph != NULL; graph = graph->next_vertex, i++);
    return i;
}

int edgeSize(Graph g){
    Graph* graph = &g;
    return graph->total_edges;
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

void neighbours(Graph g, char v){
    Graph *vertex = findVertex(&g, v);
    if (vertex == NULL) return;

    Edge *edge = vertex->edges;
    while(edge != NULL){
        printf("%c is %c neighbour\n", edge->neighbour, v);
        edge = edge->next_edge;
    }
}

void removeSingleEdge(Graph *vertex, Edge* edge_to_remove){
    if(edge_to_remove == NULL){
        printf("Skipping a nonexistent edge removal\n");
        return;
    }

    // find previous edge
    Edge *previous = NULL, *edge = vertex->edges;
    while(edge->neighbour != edge_to_remove->neighbour) { previous = edge; edge = edge->next_edge; }

    if (edge_to_remove->n_edges == 1){
        if (previous == NULL) vertex->edges = edge_to_remove->next_edge; // in case it's the first edge
        else previous->next_edge = edge_to_remove->next_edge;
        free(edge_to_remove);
    }else {
        edge_to_remove->n_edges--;
    }

}

void removeEdge(Graph *g, char v, char u){
    // locate v vertex
    Graph *v_vertex = findVertex(g, v);
    // locate u vertex
    Graph *u_vertex = findVertex(g, u);

    if (u_vertex == NULL || v_vertex == NULL) return;

    Edge *v_to_u_edge = findEdgeFromVertex(v_vertex, u);
    Edge *u_to_v_edge = findEdgeFromVertex(u_vertex, v);

    // remove v_to_u edge
    removeSingleEdge(v_vertex, v_to_u_edge);

    // remove u_to_v edge
    if (u != v) removeSingleEdge(u_vertex, u_to_v_edge);

    g->total_edges--;
}

void removeVertex(Graph *g, char v){
    if (!hasVertex(g, v)) return defaultErrorMessage();

    Graph *root = g;

    // find the vertex
    Graph *previous = g;
    while(1){
        if (g->vertex == v) break;
        previous = g;
        g = g->next_vertex;
    }

    // remove and free the correspondent edges of the removed vertex
    while(g->edges != NULL)
        removeEdge(root, g->vertex, g->edges->neighbour);

    // with all edges removed we're safe to remove and free the given vertex
    previous->next_vertex = g->next_vertex;
    free(g);

}

void endGraph(Graph *g){
    while(g->next_vertex)
        removeVertex(g, g->next_vertex->vertex);
}