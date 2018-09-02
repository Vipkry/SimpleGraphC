#include <stdio.h>
#include "grafo.h"

int main() {
    Graph graph = initGraph();
    Graph *g = &graph;

    insertVertex(g, 'A');
    insertVertex(g, 'B');
    insertVertex(g, 'E');

    insertEdge(g, 'A', 'B');
    insertEdge(g, 'A', 'E');

    removeVertex(g, 'A');
    insertVertex(g, 'A');

    insertEdge(g, 'A', 'B');
    insertEdge(g, 'A', 'E');

    printf("Edges: %d\n", edgeSize(graph));
    printf("Vertexes: %d\n", vertexSize(graph));
    return 0;
}