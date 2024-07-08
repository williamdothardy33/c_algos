#include "int_graph.h"
#include <stdlib.h>
#include "../int_queue_source/int_queue.h"

int_edge *create_int_edge(int to, int weight) {
    int_edge *edge = malloc(sizeof(int_edge));
    edge->to = to;
    edge->weight = weight;
    edge->next = NULL;
    return edge;
}

int_graph *create_int_graph(int num_vertices, int is_directed) {
    int_graph *graph = malloc(sizeof(int_graph));
    graph->num_vertices = num_vertices;
    graph->is_directed = is_directed;
    graph->num_edges = 0;
    for (int i = 1; i <= MAX_VERTICES; i++) {
        graph->vertices[i] = NULL;
        graph->degrees[i] = 0;
    }
    return graph;
}

void insert_edge(int_graph *graph, int from, int to, int weight, int is_directed) {
    int_edge *edge = create_int_edge(to, weight);
    edge->next = graph->vertices[from];
    graph->vertices[from] = edge;
    graph->degrees[from]++;

    if (!is_directed) {
        insert_edge(graph, to, from, weight, 1);
    }
    else {
        graph->num_edges++;
    }
}

void show_graph(int_graph *graph) {
    for (int i = 1; i <= graph->num_vertices; i++) {
        int_edge *current = graph->vertices[i];
        while (current != NULL) {
            printf("(from, to): (%d, %d)\n", i, current->to);\
            current = current->next;
        }
    }
}

void setup_bfs(int_graph *graph, int *discovered, int *processed, int *parents) {
    for (int i = 1; i <= graph->num_vertices; i++) {
        discovered[i] = 0;
        processed[i] = 0;
        parents[i] = -1;
    }
}

void process_before(int vertex) {
    printf("processing vertex: %d...\n", vertex);
}
void process_edge(int from, int to) {
    printf("the current vertex: %d, has the edge (from, to): (%d, %d)\n", from, from, to);
}

void process_after(int vertex) {
    printf("finished processing vertex: %d\n", vertex);
}

void bfs(int_graph *graph, int start, int discovered[], int processed[], int parents[]) {
    int_queue *queue = create_int_queue();
    enqueue(queue, start);
    discovered[start] = 1;
    int_edge *edges;
    int current;
    while (!is_empty(queue)) {
        current = dequeue(queue);
        process_before(current);
        edges = graph->vertices[current];
        while (edges != NULL) {
            int neighbor = edges->to;
            if (!processed[neighbor] || graph->is_directed) {
                process_edge(current, neighbor);
                if (!discovered[neighbor]) {
                    enqueue(queue, neighbor);
                    discovered[neighbor] = 1;
                    parents[neighbor] = current;
                }
                
            }
            edges = edges->next;
        }
        process_after(current);
        processed[current] = 1;
    }
}

void find_path(int origin, int current, int child, int parents[]) {
    if (current == origin || current == -1) {
        printf("(%d, %d) ", current, child);
    }
    else {
        find_path(origin, parents[current], current, parents);
        if (child == -1) {
            printf("%d ", current);

        }
        else {
            printf("(%d, %d) ", current, child);
        }
        if (child == -1) {
            printf("\n");
        }
    }
}

void find_connected(int_graph *graph, int discovered[], int processed[], int parents[]) {
    int component = 0;
    for (int i = 1; i <= graph->num_vertices; i++) {
        if (!discovered[i]) {
            component++;
            printf("component %d\n", component);
            printf("\n");
            bfs(graph, i, discovered, processed, parents);
        }
        
    }
}

int_graph *from_file(FILE *fp, int is_directed) {
    int num_vertices;
    int num_edges;
    int from;
    int to;
    int weight;
    
    fscanf(fp, "%d %d", &num_vertices, &num_edges);
    
    int_graph *graph = create_int_graph(num_vertices, is_directed);

    while (fscanf(fp, "%d %d %d", &from, &to, &weight) != EOF) {
        insert_edge(graph, from, to, weight, is_directed);
    }
    
    return graph;
}