#include <stdio.h>
#include <stdlib.h>
#include "graphMatriz.h"

int main() {
    Graph graph = initGraph();
    Graph *g = &graph;

    insertVertex(g, 'A');
    insertVertex(g, 'B');
    insertVertex(g, 'C');
    insertVertex(g, 'D');
    insertVertex(g, 'E');
    insertVertex(g, 'F');
    insertVertex(g, 'G');

    insertEdge(g, 'A', 'B');
    insertEdge(g, 'A', 'B');

    insertEdge(g, 'A', 'C');
    insertEdge(g, 'A', 'C');
    insertEdge(g, 'A', 'C');
    insertEdge(g, 'A', 'C');

    insertEdge(g, 'B', 'C');

    insertEdge(g, 'B', 'D');
    insertEdge(g, 'B', 'D');
    insertEdge(g, 'B', 'D');

    insertEdge(g, 'B', 'E');
    insertEdge(g, 'B', 'E');
    insertEdge(g, 'B', 'E');
    insertEdge(g, 'B', 'E');
    insertEdge(g, 'B', 'E');

    insertEdge(g, 'C', 'D');
    insertEdge(g, 'C', 'D');
    insertEdge(g, 'C', 'D');
    insertEdge(g, 'C', 'D');
    insertEdge(g, 'C', 'D');

    insertEdge(g, 'C', 'F');
    insertEdge(g, 'C', 'F');
    insertEdge(g, 'C', 'F');
    insertEdge(g, 'C', 'F');
    insertEdge(g, 'C', 'F');
    insertEdge(g, 'C', 'F');

    insertEdge(g, 'D', 'E');
    insertEdge(g, 'D', 'E');
    insertEdge(g, 'D', 'E');

    insertEdge(g, 'D', 'F');

    insertEdge(g, 'E', 'F');
    insertEdge(g, 'E', 'F');
    insertEdge(g, 'E', 'F');
    insertEdge(g, 'E', 'F');
    insertEdge(g, 'E', 'F');
    insertEdge(g, 'E', 'F');
    insertEdge(g, 'E', 'F');
    insertEdge(g, 'E', 'F');
    insertEdge(g, 'E', 'F');

    insertEdge(g, 'E', 'G');
    insertEdge(g, 'E', 'G');
    insertEdge(g, 'E', 'G');
    insertEdge(g, 'E', 'G');
    insertEdge(g, 'E', 'G');

    insertEdge(g, 'F', 'G');

    dijkstra(g, 'A');


//    printf("A->B: %d\n", isNeighbour(graph, 'A', 'B'));
//    printf("E->B: %d\n", isNeighbour(graph, 'E', 'B'));

    neighbours(graph, 'D');

    printf("Edges: %d\n", edgeSize(graph));
    printf("Vertexes: %d\n", vertexSize(graph));

    endGraph(g);
    return 0;
}
