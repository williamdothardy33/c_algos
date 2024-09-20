#include "combinatorics.h"
#include <stdlib.h>

int has_combination_size(int combination[], int in_offset, void *combination_size) {
    int combination_length = *(int *)(combination_size);
    return in_offset == combination_length;
}

void show_combination(int combination[], int in_offset, void *combination_size) {
    int combination_length = *(int *)(combination_size);
    int result[in_offset + 1];
    int result_offset = 0;
    for (int i = 1; i <= combination_length; i++) {
        if (combination[i]) {
            result_offset++;
            result[result_offset] = i;
        }
    }
    printf("[");
    if (result_offset > 0) {
        for (int i = 1; i < result_offset; i++) {
            printf("%d, ", result[i]);
        }
        printf("%d", result[result_offset]);
    }
    printf("]\n");
}

void set_indicators(int combination[], int in_offset, int combination_indicators[], int *items_size, void *aux) {
    *items_size = 0;
    for (int i = 1; i >= 0; i--) {
        combination_indicators[1 - i] = i;
        (*items_size) += 1;
    }
}


int has_permutation_size(int permutation[], int in_offset, void *permutation_size) {
    int permutation_length = *(int *)(permutation_size);
    return in_offset == permutation_length;
}

void set_permutation_choices(int permutation[], int in_offset, int permutation_choices[], int *items_size, void *permutation_size) {
    int permutation_length = *(int *)(permutation_size);
    int permutation_indicator[permutation_length];
    for (int i = 1; i <= permutation_length; i++) {
        permutation_indicator[i] = 0;
    }
    for (int j = 1; j <= permutation_length; j++) {
        permutation_indicator[permutation[j]] = 1;
    }
    *items_size = 0;
    int choices_offset = 1;
    while (choices_offset <= permutation_length) {
        if (!permutation_indicator[choices_offset]) {
            permutation_choices[*items_size] = choices_offset;
            (*items_size) += 1;
        }
        choices_offset += 1;
    }
}

void show_permutation(int permutation[], int in_offset, void *permutation_size) {
    int permutation_length = *(int *)(permutation_size);
    printf("[");
    for (int i = 1; i < permutation_length; i++) {
        printf("%d, ", permutation[i]);
    }
    printf("%d]\n", permutation[permutation_length]);
}

void undo_last_choice(int permutation[], int in_offset, void *aux) {
    permutation[in_offset] = 0;
}

graph_search_term *create_graph_search_term(int_graph *graph, int origin, int target) {
    graph_search_term *search_term = malloc(sizeof(graph_search_term));
    int *edge_origins = malloc(sizeof(int) * (graph->num_vertices + 1));
    search_term->edge_origins = edge_origins;
    for (int i = 1; i <= graph->num_vertices; i++) {
        search_term->edge_origins[i] = -1;
    }
    
    search_term->graph = graph;
    search_term->origin = origin;
    search_term->current = origin;
    search_term->target = target;
    return search_term;
}

int reached_target(int visited_vertices[], int in_offset, void *data) {
    graph_search_term search_term = *(graph_search_term *)(data);
    //printf("a path was found is %d\n", visited_vertices[in_offset] == search_term.target);
    return visited_vertices[in_offset] == search_term.target;
}

void set_undiscovered_vertices(int visited_vertices[], int in_offset, int undiscovered_vertices[], int *items_size, void *data) {
    graph_search_term *search_term = (graph_search_term *)(data);
    printf("in this recursive call current is %d\n", search_term->current);
    *(items_size) = 0;
    if (in_offset == 1) {
        undiscovered_vertices[*(items_size)] = search_term->origin;
        *(items_size) += 1;
        search_term->current = search_term->origin;
        //printf("item size is %d\n", *(items_size));

    }
    else {

        int vertices_indicator[search_term->graph->num_vertices + 1];
        for (int i = 1; i <= search_term->graph->num_vertices; i++) {
            vertices_indicator[i] = 0;
        }

        for (int j = 1; j < in_offset; j++) {
            vertices_indicator[visited_vertices[j]] = 1;
        }

        int current = search_term->current;
        int_edge *edges = search_term->graph->vertices[current];
        while (edges != NULL) {
            if (!vertices_indicator[edges->to]) {
                printf("edges to for %d is %d\n", current, edges->to);
                undiscovered_vertices[*(items_size)] = edges->to;
                *(items_size) += 1;
            }
            edges = edges->next;
        }
    }
}

void pre_visit(int visited_vertices[], int in_offset, void *data) {
    graph_search_term *search_term = (graph_search_term *)(data);
    int origin = search_term->current;
    int current = visited_vertices[in_offset];
    printf("(origin, current) is (%d, %d)\n", origin, current);
    search_term->current = current;
    search_term->edge_origins[current] = origin;
}

void post_visit(int visited_vertices[], int in_offset, void *data) {
    graph_search_term *search_term = (graph_search_term *)(data);
    int origin = search_term->edge_origins[search_term->current];
    search_term->edge_origins[search_term->current] = -1;
    search_term->current = origin;
}

void show_path(int visited_vertices[], int in_offset, void *data) {
    graph_search_term search_term = *(graph_search_term *)(data);
    find_path(search_term.origin, search_term.target, -1, search_term.edge_origins);
}




void do_nothing_combo(int solution[], int in_offset, void *aux) {}


void combinations(int size) {
    int combination[MAX_SIZE] = {0};
    backtrack(combination
    , 0
    , has_combination_size
    , show_combination
    , set_indicators
    , do_nothing_combo
    , do_nothing_combo
    , &size);
}

void permutations(int size) {
    int permutation[MAX_SIZE] = {0};
    backtrack(permutation
    , 0
    , has_permutation_size
    , show_permutation
    , set_permutation_choices
    , do_nothing_combo
    , undo_last_choice
    , &size);
}

void list_paths(int_graph *graph, int from, int to) {
    graph_search_term *search_term = create_graph_search_term(graph, from, to);
    int visited_vertices[graph->num_vertices + 1];
    for (int i = 1; i <= graph->num_vertices; i++) {
        visited_vertices[i] = 0;
    }
    backtrack(visited_vertices
    , 0
    , reached_target
    , show_path
    , set_undiscovered_vertices
    , pre_visit
    , post_visit
    , search_term);
}

int main(void) {
    //combinations(3);
    //permutations(3);

    FILE *fp;
    int num_vertices;
    int num_edges;
    int origin;
    int destination;

    char *filename = "../int_graph_source/test_graph_connected.txt";
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("warning couldn't open file: %s\n", filename);
        return 0;
    }

    int_graph *graph = from_file(fp, 0);
    list_paths(graph, 1, 4);
}