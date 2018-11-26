/* There are 26 uppercase letters available in ASCII table
*  as they're going to be used as vertexes indexes, we can restrict
*  the maximum number of vertexes as 26 */
#define MAX_ROW_SIZE 26

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
int vertexSize(Graph g);
int edgeSize(Graph g);
void endGraph(Graph *g);