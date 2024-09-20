#include "../int_graph_source/int_graph.h"
#define MAX_CANDIDATES 20
#define MAX_SIZE 20
#define finished 0

int is_solution(int solution[], int in_offset, void *aux);
void process_solution(int solution[], int in_offset,  void *aux);
void next_candidates(int solution[], int in_offset, int next_items[], int *items_size, void *aux);
void apply(int solution[], int in_offset, void *aux);
void un_apply(int solution[], int in_offset, void *aux);

void backtrack(int solution[]
, int in_offset
, int (*is_solution)(int[], int, void *)
, void (*process_solution)(int[], int, void *)
, void (*next_candidates)(int[], int, int[], int *, void *)
, void (*apply)(int[], int, void *)
, void (*un_apply)(int[], int, void *)
, void *aux);

struct graph_search_term {
    int origin;
    int current;
    int target;
    int *edge_origins ;
    int_graph *graph;
};
typedef struct graph_search_term graph_search_term;

//graph_search_term *create_graph_search_term(int_graph *graph, int origin, int target);