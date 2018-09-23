struct vertex_node {
    char vertex;
    int total_edges;
    struct vertex_node* next_vertex;
    struct edge_node* edges;
};

struct edge_node {
    char neighbour;
    int n_edges;
    struct edge_node* next_edge;
};

typedef struct vertex_node Graph;
typedef struct edge_node Edge;

Graph initGraph();
void insertVertex(Graph *g, char v);
void insertEdge(Graph *g, char v, char u);
void removeVertex(Graph *g, char v);
//void removeEdge(Graph *g, char v, char u);
int isNeighbour(Graph g, char v, char u);
void neighbours(Graph g, char v);
int vertexSize(Graph g);
int edgeSize(Graph g);
//void endGraph(Graph *g);