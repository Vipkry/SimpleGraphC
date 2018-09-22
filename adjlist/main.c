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

//    printf("%c\n", g->next->vertex);
//    printf("%c\n",g->next->next->vertex);
//    printf("%c\n",g->next->next->next->vertex);
//    printf("%c\n",g->next->next->next->next->vertex);

//    insertEdge(g, 'A', 'B');
//    insertEdge(g, 'A', 'E');
//
    removeVertex(g, 'A');
    insertVertex(g, 'A');
//
//    insertEdge(g, 'A', 'B');
//    insertEdge(g, 'A', 'E');
//    insertEdge(g, 'A', 'A');
//
//    printf("A->B: %d\n", isNeighbour(graph, 'A', 'B'));
//    printf("E->B: %d\n", isNeighbour(graph, 'E', 'B'));
//
//    neighbours(graph, 'A');
//
//    printf("Edges: %d\n", edgeSize(graph));
//    printf("Vertexes: %d\n", vertexSize(graph));
//
//    endGraph(g);
    return 0;
}