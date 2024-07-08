#include "int_graph.h"
int main(void) {
    FILE *fp;
    int num_vertices;
    int num_edges;
    int origin;
    int destination;

    fp = fopen("./test_graph.txt", "r");
    int_graph *graph = from_file(fp, 0);
    show_graph(graph);
    /*fscanf(fp, "%d %d", &num_vertices, &num_edges);
    printf("the graph has %d vertices with %d edges\n", num_vertices, num_edges);
    while (fscanf(fp, "%d %d", &origin, &destination) != EOF) {
        printf("the graph has edge (origin, destination): (%d, %d)\n", origin, destination);
    }*/
    printf("\n");
    int discovered[graph->num_vertices + 1];
    int processed[graph->num_vertices + 1];
    int parents[graph->num_vertices + 1];
    int start = 1;
    setup_bfs(graph, discovered, processed, parents);
    //bfs(graph, start, discovered, processed, parents);
    //printf("\n");
    find_connected(graph, discovered, processed, parents);\
    printf("\n");
    find_path(start, 4, -1, parents);
    fclose(fp);
}