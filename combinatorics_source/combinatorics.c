#include "combinatorics.h"
/**
we would like to find or enumerate and exhaustive set of well defined sequences of items. suppose that for any 
prefix sequence of items for a sequence in this exhaustive set there is a way to construct candidates for the next
entry in the sequence. from any such prefix sequence the set of candidates for the next item in the sequence can be
viewed as a tree with parent node representing the last entry in the prefix and children nodes as the next candidate
item in the sequence. this is the strategy of the backtrack algorithm below. to construct candidates we might need to know
the current prefix, how many items are in the prefix, a temporary storage area for the next candidate elements in the sequence
how many candidates there are. a condition to evaluate when we have a solution. a way to construct the next set of candidates
pre-order processing based on the current prefix, post order processing, and what to do when you've found a solution. 
 */

void backtrack(int solution[]
, int in_offset
, int (*is_solution)(int[], int, void *)
, void (*process_solution)(int[], int, void *)
, void (*next_candidates)(int[], int, int[], int *, void *)
, void (*apply)(int[], int, void *)
, void (*un_apply)(int[], int, void *)
, void *aux) {
    if (!finished) {
        if (is_solution(solution, in_offset, aux)) {
            process_solution(solution, in_offset, aux);
        }
        else {
            int next_items[MAX_CANDIDATES];
            int next_item;
            int items_size;
            in_offset++;
            next_candidates(solution, in_offset, next_items, &items_size, aux);
            for (int i = 0; i < items_size; i++) {
                next_item = next_items[i];
                solution[in_offset] = next_item;
                apply(solution, in_offset, aux);
                backtrack(solution, in_offset, is_solution, process_solution, next_candidates, apply, un_apply, aux);
                un_apply(solution, in_offset, aux);
            }
        }
    }
}
