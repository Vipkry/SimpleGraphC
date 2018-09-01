#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

Graph initGraph(){
    Graph* g = (Graph *) malloc(sizeof(Graph));
    return *g;
}