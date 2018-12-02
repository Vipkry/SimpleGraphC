#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graphLista.h"

/* Maps vertex char to int.
*  Uppercase letters only */
int to_int(char c){ ;
    return (int) c - (int) 'A';
}

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
    g->vertex = ROOT_VERTEX; // first vertex will always be ROOT_VERTEX for simplification purposes
    g->total_edges = 0;
    g->edges = NULL;
    g->next_vertex = NULL;
    return *g;
}


/* Find and returns vertex in given graph */
Graph* findVertex(Graph *g, char v){
    while (g != NULL){
        if(g->vertex == v) return g;
        g = g->next_vertex;
    }

    defaultErrorMessage();
    return NULL;

}

/* Find edge in given edge */
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
    newGraph->edges = NULL;
    newGraph->total_edges = 0;
    g->next_vertex = newGraph;
}

/* Aux function to help insertEdge function.
 * will insert only one edge with g as origin and new_neighbour as destination*/
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

        Edge *last_edge = g->edges;
        if (last_edge != NULL){
            // find last_edge
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
    // loop though the list ignoring the root ('\0').
    for(i = -1; graph != NULL; graph = graph->next_vertex, i++);
    return i;
}

int edgeSize(Graph g){
    return g.total_edges; //just get the stored value, that will be O(1) instead of O(n*m)
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

/* Removes single edge without worrying about it's pair in the unidirectional graph
 * specially useful for edges with same origin and destination */
void removeSingleEdge(Graph *vertex, Edge* edge_to_remove){
    if(edge_to_remove == NULL){
        printf("Skipping a nonexistent edge removal\n");
        return;
    }

    // find previous edge
    Edge *previous = NULL, *edge = vertex->edges; // *edge is only an aux var here
    while(edge->neighbour != edge_to_remove->neighbour) { previous = edge; edge = edge->next_edge; }

    if (edge_to_remove->n_edges == 1){
        // in case it's the first edge set vertex ptr to next_edge
        if (previous == NULL) vertex->edges = edge_to_remove->next_edge;
        // else: it's not the first edge of the vertex so just skip it in the edges list of that vertex
        else previous->next_edge = edge_to_remove->next_edge;

        free(edge_to_remove);
    }else {
        edge_to_remove->n_edges--; // in case of multiple edges
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
    while(g->edges != NULL) removeEdge(root, g->vertex, g->edges->neighbour);

    // with all edges removed we're safe to remove and free the given vertex
    previous->next_vertex = g->next_vertex;
    free(g);

}

void endGraph(Graph *g){
    while(g->next_vertex)
        removeVertex(g, g->next_vertex->vertex);
}

void dijkstra(Graph *g, char s){
    if (!hasVertex(g, s)) return defaultErrorMessage();

    int i, dist_adj;
    Graph *x;

    char* queue      = NULL; //dijkstra_queue(g, s);
    char* prev       = (char *) malloc(sizeof(char)  * MAX_SIZE);
    int * dist       = (int *)  malloc(sizeof(int)   * MAX_SIZE);
    int * verified   = (int *)  malloc(sizeof(int)   * MAX_SIZE);

    for (i = 0; i < MAX_SIZE; i++)
    {
        dist[i] = INT_MAX;
        prev[i] = '-';
        verified[i] = 0;
    }

    dist[to_int(s)] = 0;

    for (i = 0; queue[i] != '\0'; i++)
    {
        x = findVertex(g, queue[i]);
        Edge *neighbor = x->edges;
        // for all neighbors
        while(neighbor)
        {
            dist_adj = neighbor->n_edges;
            int j = to_int(neighbor->neighbour);
            // if it was not yet marked as verified[]
            // and its distance should be updated
            // != INT_MAX protection against integer overflowing
            if (verified[j] == 0 && dist[j] > dist[to_int(x->vertex)] + dist_adj && dist[to_int(x->vertex)] != INT_MAX)
            {
                dist[j] = dist[to_int(x->vertex)] + dist_adj;
                prev[j] = x->vertex;
            }
            neighbor = neighbor->next_edge;
        }

        verified[to_int(x->vertex)] = 1;
    }

    Graph* aux = g;
    while(aux)
    {
        int j = to_int(aux->vertex);
        printf("dist[%c] = %d \t\t pai[%c] = %c\n", aux->vertex, dist[j], aux->vertex, prev[j]);

        aux = aux->next_vertex;
    }

    free(dist);
    free(prev);
    free(verified);
    free(queue);
}