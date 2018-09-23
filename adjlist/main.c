#include <stdio.h>
#include <stdlib.h>
#include "graphLista.h"

int main() {
    Graph graph = initGraph();
    Graph *g = &graph;

    insertVertex(g, 'A');
    insertVertex(g, 'E');
    insertVertex(g, 'C');
    insertVertex(g, 'D');
    insertVertex(g, 'B');

    insertEdge(g, 'A', 'B');
    insertEdge(g, 'A', 'E');

    removeVertex(g, 'A');
    insertVertex(g, 'A');

    printf("%c\n", g->next_vertex->vertex);
    printf("%c\n",g->next_vertex->next_vertex->vertex);
    printf("%c\n",g->next_vertex->next_vertex->next_vertex->vertex);
    printf("%c\n",g->next_vertex->next_vertex->next_vertex->next_vertex->vertex);

    insertEdge(g, 'A', 'B');
    insertEdge(g, 'E', 'C');
    insertEdge(g, 'A', 'A');

    printf("A->B: %d\n", isNeighbour(graph, 'A', 'B'));
    printf("E->B: %d\n", isNeighbour(graph, 'E', 'B'));

    neighbours(graph, 'A');

    printf("Edges: %d\n", edgeSize(graph));
    printf("Vertexes: %d\n", vertexSize(graph));
//
//    endGraph(g);
    return 0;
}