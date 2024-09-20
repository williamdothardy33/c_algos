#include "int_graph.h"
#include <stdlib.h>

void show_vertex_before(int vertex);
void show_vertex_after(int vertex);
void show_edge_type(int from, int to);

int main(void) {
    FILE *fp;
    int num_vertices;
    int num_edges;
    int origin;
    int destination;

    //fp = fopen("./test_graph_1.txt", "r");
    //int_graph *graph = from_file(fp, 0);
    char *filename = "./test_graph_connected.txt";
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("warning couldn't open file: %s\n", filename);
        return 0;
    }
    int_graph *graph = from_file(fp, 0);
    //adjacency_matrix *matrix = from_file_1(fp, 0);
    //show_matrix(matrix);
    //show_graph(graph);
    //int degree_sum = sum_degree(graph->degrees, graph->num_vertices);
    //printf("the sum of degree is: %d", degree_sum);
    printf("\n");
    


    /*int discovered[graph->num_vertices + 1];
    int processed[graph->num_vertices + 1];
    int parents[graph->num_vertices + 1];
    int stack_indicies[graph->num_vertices + 1], earliest_returns[graph->num_vertices + 1], num_branches[graph->num_vertices + 1];*/
    int start = 1;

    
    //bfs_0(graph, start, discovered, processed, parents);
    //printf("\n");
    //print_connected(graph, discovered, processed, parents);
    //printf("\n");

    bfs_1(graph, start, show_vertex_before, show_edge_type, show_vertex_after);
    find_path_bfs(1, 4, -1);
    //printf("\n");

    //setup_search(graph, discovered, processed, parents);
    //dfs_0(graph, start, discovered, processed, parents, show_vertex_before, show_edge_type, show_vertex_after);
    //printf("\n");

    //setup_search(graph, discovered, processed, parents);
    //dfs_1(graph, start, discovered, processed, parents, show_vertex_before, show_edge_type, show_vertex_after);
    //printf("\n");

    //setup_search(graph, discovered, processed, parents);
    //dfs_1(graph, start, discovered, processed, parents, show_vertex_before, show_cycle, show_vertex_after);
    //printf("\n");

    //setup_search(graph);
    //set_stack_level(graph);
    //dfs_1(graph, start, stack_level_before, show_edge_type, stack_level_after);
    //printf("\n");

    //setup_search(graph);
    //setup_cut_node_search(graph);
    //set_stack_level(graph);
    //dfs_1(graph, start, visit_node, process_branch, leave_node);
    //printf("\n");

    //setup_search(graph);
    //set_stack_level(graph);
    //topo_sort(graph);
    //show_topo();
    //printf("\n");

    //strongly_connected(graph);

    //two_color(graph, discovered, processed, parents);

    //int_graph *graph_transposed = transpose(graph);
    //show_graph(graph_transposed);
    //int min_weight = prims_algo(graph, 1);
    //printf("the minimum weight spanning tree using prim has weight %d\n", min_weight);

    /*edge_pair *pairs = edge_pairs_from(graph, 1);
    for (int i = 1; i <= graph->num_edges; i++) {
        int vertex_1 = pairs[i].vertex_1;
        int vertex_2 = pairs[i].vertex_2;
        int weight = pairs[i].weight;
        printf("the vertices %d and %d are joined by an edge with weight %d\n", vertex_1, vertex_2, weight);

    }*/

    //qsort(pairs, graph->num_edges, sizeof(edge_pair), compare_weight);
    //edge_pair last = pairs[graph->num_edges];
    //printf("after sorting...\n");
    //printf("last one has (%d, %d) with weight %d", last.vertex_1, last.vertex_2, last.weight);

    /*for (int i = 1; i <= graph->num_edges; i++) {
        int vertex_1 = pairs[i].vertex_1;
        int vertex_2 = pairs[i].vertex_2;
        int weight = pairs[i].weight;
        printf("the vertices %d and %d are joined by an edge with weight %d\n", vertex_1, vertex_2, weight);

    }*/
    //printf("\n");
    //int min_weight_1 = kruskal(graph);
    //printf("the minimum weight spanning tree using kruskal has weight %d\n", min_weight_1);

    //dijkstra(graph, start);
    fclose(fp);
}