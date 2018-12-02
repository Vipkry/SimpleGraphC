#include <stdio.h>
#include "graphIncid.h"

int main() {
    Graph g = initGraph();
    int op = -1;
    char v, u;

    scanf("%d", &op);
    while (op != 0) {
        // inserção de um novo vértice
        if (op == 1) {
            scanf(" %c", &v);
            insertVertex(&g, v);
        }
        // inserção de uma nova aresta
        if (op == 2)  {
            scanf(" %c %c", &v, &u);
            insertEdge(&g, v, u);
        }
        // remoção de um vértice já existente
        if (op == 3)  {
            scanf(" %c", &v);
            removeVertex(&g, v);
        }
        // remoção de uma aresta já existente
        if (op == 4)  {
            scanf(" %c %c", &v, &u);
            removeEdge(&g, v, u);
        }
        // determinar se dois vértices são adjacentes
        if (op == 5)  {
            scanf(" %c %c", &v, &u);
            if (isNeighbour(g, v, u)) printf("Os vertices %c e %c sao adjacentes\n", v, u);
            else printf("Os vertices %c e %c nao sao adjacentes\n", v, u);
        }
        // imprime todos os vizinhos de um vértice
        if (op == 6)  {
            scanf(" %c", &v);
            neighbours(g, v);
        }
        // determinar número de vértices
        if (op == 7)  {
            printf("O numero de vertices eh: %d\n", vertexSize(g));
        }
        // determinar número de arestas
        if (op == 8)  {
            printf("O numero de arestas eh: %d\n", edgeSize(g));
        }
        scanf("%d", &op);

    }
    endGraph(&g);

    return 0;
}