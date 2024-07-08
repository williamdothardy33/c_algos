#include <stdio.h>
#define MAX_VERTICES 100
struct int_edge {
    int to;
    int weight;
    struct int_edge *next;
};

typedef struct int_edge int_edge;

int_edge *create_int_edge(int to, int weight);


struct int_graph {
    int_edge *vertices[MAX_VERTICES + 1];
    int degrees[MAX_VERTICES + 1];
    int num_vertices;
    int num_edges;
    int is_directed;
};

typedef struct int_graph int_graph;

int_graph *create_int_graph(int num_vertices, int is_directed);
void insert_edge(int_graph *graph, int from, int to, int weight, int is_directed);
int_graph *from_file(FILE *fp, int is_directed);
void show_graph(int_graph *graph);
void bfs(int_graph *graph, int start, int discovered[], int processed[], int parents[]);
void find_path(int origin, int current, int parent, int parents[]);
void setup_bfs(int_graph *graph, int discovered[], int processed[], int parents[]);
void find_connected(int_graph *graph, int discovered[], int processed[], int parents[]);