#include <stdio.h>
#include "../int_stack_source_v2/int_stack.h"
#define MAX_VERTICES 100
#define SET_SIZE 20
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
void find_path(int origin, int current, int child, int parents[]);
void find_path_bfs(int origin, int current, int child);
void setup_search(int_graph *graph);
void setup_cut_node_search(int_graph *graph);
void print_connected(int_graph *graph, void (*process_before)(int), void (*process_edge)(int, int), void (*process_after)(int));
int sum_degree(int *degrees, int num_vertices);
int two_color(int_graph *graph);
void show_cycle(int from, int to);
void set_stack_level(int_graph *graph);
void stack_level_before(int from);
void stack_level_after(int from);
void visit_node(int from);
void process_branch(int from, int to);
void leave_node(int from);
void do_nothing(int from, int to);
void do_nothing_1(int from);
void proper_dependents(int from, int to);
void add_dependents_of(int required);
void topo_sort(int_graph *graph);
void show_topo();
void process_node(int from);
int_graph *transpose(int_graph* graph);
void strongly_connected(int_graph *graph);
int prims_algo(int_graph *graph, int start);
int dijkstra(int_graph *graph, int start);


enum edge_type {
    TREE, BACK, FORWARD, CROSS
};

typedef enum edge_type edge_type;

enum color {
    BLACK, WHITE, UNCOLORED
};

typedef enum color color;

struct edge_pair {
    int vertex_1;
    int vertex_2;
    int weight;
};

typedef struct edge_pair edge_pair;

edge_pair *edge_pairs_from(int_graph *graph, int start);
edge_pair *edge_pairs_from_v1(int_graph *graph);
void dfs_weighted(int_graph *graph, int start, void (*process_before)(int), void (*process_edge)(int, int, int), void (*process_after)(int));
int compare_weight(const void *ep_1, const void *ep_2);

struct union_find {
    int parents[SET_SIZE + 1];
    int component_partition_size[SET_SIZE + 1];
    int num_partitions;
};

typedef struct union_find union_find;

union_find *create_union_find();
int kruskal(int_graph *graph);

struct adjacency_matrix {
    int edge_weights[MAX_VERTICES + 1][MAX_VERTICES + 1];
    int num_vertices;
};

typedef struct adjacency_matrix adjacency_matrix;

adjacency_matrix *create_adjacency_matrix();
adjacency_matrix *from_file_1(FILE *fp, int is_directed);
void show_matrix(adjacency_matrix *matrix);