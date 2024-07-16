#include "int_graph.h"

void show_vertex_before(int vertex);
void show_vertex_after(int vertex);
void show_edge_type(int from, int to);

int main(void) {
    FILE *fp;
    int num_vertices;
    int num_edges;
    int origin;
    int destination;

    fp = fopen("./test_graph_1.txt", "r");
    int_graph *graph = from_file(fp, 0);
    //show_graph(graph);
    //int degree_sum = sum_degree(graph->degrees, graph->num_vertices);
    //printf("the sum of degree is: %d", degree_sum);
    //printf("\n");
    


    /*int discovered[graph->num_vertices + 1];
    int processed[graph->num_vertices + 1];
    int parents[graph->num_vertices + 1];
    int stack_indicies[graph->num_vertices + 1], earliest_returns[graph->num_vertices + 1], num_branches[graph->num_vertices + 1];*/
    int start = 1;

    
    //bfs_0(graph, start, discovered, processed, parents);
    //printf("\n");
    //print_connected(graph, discovered, processed, parents);
    //printf("\n");

    //bfs_1(graph, start, discovered, processed, parents, show_vertex_before, show_edge_type, show_vertex_after);
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

    //setup_search(graph, discovered, processed, parents);
    //set_stack_level();
    //dfs_1(graph, start, stack_level_before, show_edge_type, stack_level_after);
    //printf("\n");

    setup_search(graph);
    setup_cut_node_search(graph);
    set_stack_level();
    dfs_1(graph, start, visit_node, process_branch, leave_node);
    printf("\n");

    //two_color(graph, discovered, processed, parents);
    fclose(fp);
}