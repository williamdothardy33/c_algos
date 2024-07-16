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
void bfs_0(int_graph *graph, int start, void (*process_before)(int), void (*process_edge)(int, int), void (*process_after)(int));
void bfs_1(int_graph *graph, int start, void (*process_before)(int), void (*process_edge)(int, int), void (*process_after)(int));
void dfs_0(int_graph *graph, int start, void (*process_before)(int), void (*process_edge)(int, int), void (*process_after)(int));
void dfs_1(int_graph *graph, int start, void (*process_before)(int), void (*process_edge)(int, int), void (*process_after)(int));
void find_path(int origin, int current, int parent, int parents[]);
void setup_search(int_graph *graph);
void setup_cut_node_search(int_graph *graph);
void print_connected(int_graph *graph, void (*process_before)(int), void (*process_edge)(int, int), void (*process_after)(int));
int sum_degree(int *degrees, int num_vertices);
int two_color(int_graph *graph);
void show_cycle(int from, int to);
void set_stack_level();
void stack_level_before(int from);
void stack_level_after(int from);
void visit_node(int from);
void process_branch(int from, int to);
void leave_node(int from);

enum edge_type {
    TREE, BACK
};

typedef enum edge_type edge_type;

enum color {
    BLACK, WHITE, UNCOLORED
};

typedef enum color color;