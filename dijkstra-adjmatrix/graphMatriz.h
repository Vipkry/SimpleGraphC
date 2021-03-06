struct graph {
    int edges;
    int* vertexes;
    int** matrix;
};

typedef struct graph Graph;

Graph initGraph();
void insertVertex(Graph *g, char v);
void insertEdge(Graph *g, char v, char u);
void removeVertex(Graph *g, char v);
void removeEdge(Graph *g, char v, char u);
int isNeighbour(Graph g, char v, char u);
void neighbours(Graph g, char v);
void dijkstra(Graph *g, char s);
int vertexSize(Graph g);
int edgeSize(Graph g);
void endGraph(Graph *g);
