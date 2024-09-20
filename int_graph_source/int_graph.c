#include "int_graph.h"
#include <stdint.h>
#include <stdlib.h>
#include "../int_queue_source/int_queue.h"

int terminate_search;
int push_count;
int last_push_index;
int pop_count;
color colors[MAX_VERTICES + 1];
int bipartite;
int num_branches[MAX_VERTICES + 1];
int stack_indicies[MAX_VERTICES + 1];
int earliest_returns[MAX_VERTICES + 1];
int recursive_steps[MAX_VERTICES + 1];
int discovered[MAX_VERTICES + 1], processed[MAX_VERTICES + 1], parents[MAX_VERTICES + 1];
int_stack *required_by; //top always required by remaining in the stack
edge_pair edges[MAX_VERTICES + 1];
int in_offset;

void setup_cut_node_search(int_graph *graph) {
    for (int i = 1; i <= graph->num_vertices; i++) {
        stack_indicies[i] = graph->num_vertices + 1;
        earliest_returns[i] = graph->num_vertices + 1;
        num_branches[i] = 0;

    }
}

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

/**
show graph will traverse every edge in the graph. for a complete undirected graph with n vertices this will be n(n - 1) edges.
for a graph with an average out degree of k it will be nk. (the book says n(n - 1) / 2 I'm assuming (x, y), (y, x) are the same edge
but this implementation of insert_edge will create 2 edges if it is undirected)
 */

void show_graph(int_graph *graph) {
    for (int i = 1; i <= graph->num_vertices; i++) {
        int_edge *current = graph->vertices[i];
        while (current != NULL) {
            printf("(from, to): (%d, %d)\n", i, current->to);\
            current = current->next;
        }
    }
}

void setup_search(int_graph *graph) {
    for (int i = 1; i <= graph->num_vertices; i++) {
        discovered[i] = 0;
        processed[i] = 0;
        parents[i] = -1;
    }
}

edge_type edge_type_from(int from, int to) {
    if (!discovered[to] || parents[to] == from) {
        return TREE; 
    }
    else if (discovered[to] && !processed[to]) {
        return BACK; //!processed[to] means "to" is still on the stack which means "from" must be a descendent of "to"
                    //since parent edges aren't processed "to" must be a direct ancestor that is not "from's" parent 
    }
    else if (processed[to] && stack_indicies[to] > stack_indicies[from]) {
        return FORWARD; //reached "to" in a directed graph and had to return to 
                        //"from" (the first return with additional outgoing edges that happen
                        //to go to "to") because reached a dead end at "to" or at one of it's descendents ("to" or 
                        //one of it's descendents doesn't have outgoing links)
                        // "to" started and finished processing after "from" via "one of from's descendents
    }
    else if (processed[to] && recursive_steps[to] < recursive_steps[from]){
        return CROSS; //recursive_steps[to] < recursive_steps[from] implies "to" was discovered before "from", which implies "from"
                    //cannot be a "direct" ancestor of "from" in the dfs tree. processed[to] implies all outgoing edges from "to" and
                    //it descendents where processed before "from" was discovered. this implies that "from" lies on a different subtree than
                    //"to"
    }
    else {
        printf("cannot classify edge\n");
        return -1;
    }
}

void show_vertex_before(int vertex) {
    printf("\n");
    printf("processing vertex: %d...\n", vertex);
}

void show_vertex_after(int vertex) {
    printf("finished processing vertex: %d\n", vertex);
    printf("\n");
}

void show_edge(int from, int to) {
    printf("the edge (%d, %d) is being processed\n", from, to);
}
void show_edge_type(int from, int to) {
    edge_type type = edge_type_from(from, to);
    char *result;
    switch (type) {
        case TREE:
            result = "TREE";
            break;
        case BACK:
            result = "BACK";
            break;
        case FORWARD:
            result = "FORWARD";
            break;
        case CROSS:
            result = "CROSS";
            break;
        default:
            result = " ";
            break;
    }
    printf("the edge (from, to): (%d, %d) is a %s edge\n", from, to, result);
}

/**
bfs_0 traverses the edges forming the connected component of a graph where the start is a member of the set of vertices that
form the edges of the connected component. bfs_0 will always selected edges to process for which the destination endpoint hasn't 
been discovered. The edges selected for processing form a tree where earlier discovered vertices sit at higher levels in the tree
starting at the root with start. each node that is the origin of an edge will only point to children nodes.
the traversal tree is formed level by level where each level after the root contained the undiscovered children node of the previous
level parent node bfs_0 will not process all edges
 */

void bfs_0(int_graph *graph, int start, void (*process_before)(int), void (*process_edge)(int, int), void (*process_after)(int)) {
    setup_search(graph);
    int_queue *queue = create_int_queue();
    enqueue(queue, start);
    discovered[start] = 1;
    int_edge *edges;
    int from;

    while (!is_empty(queue)) {
        from = dequeue(queue);
        process_before(from);
        edges = graph->vertices[from];
        while (edges != NULL) {
            int to = edges->to;
            if (!discovered[to]) {
                parents[to] = from;
                process_edge(from, to);
                enqueue(queue, to);
                discovered[to] = 1;
            }
            edges = edges->next;
        }
        process_after(from);
        processed[from] = 1;
    }

}


/**
bfs_1 is similar to bfs_0 with the difference being the bfs_1 condition to select edges for processing is only that
the destination hasn't been processed.
(a vertex being processed means it has been extracted from the queue and its undiscovered neighbors have been put in the queue at the minimum)
a vertex that hasn't been processed can either be undiscovered in which case it will have its parent updated to the current vertex, or discovered.
I think a condition for being discovered is that a parent node must have been processed which implies that the discovered node is in the queue.
at most 2 contiguous level nodes from the tree generated by the traversal can be in the queue I think. 3 situations I can think of is same level nodes in the queue
parent and child nodes from the same subtree or child and parent nodes from different subtrees. point is the process_edge function will only consider tree edges or
edges for whom the destination is on the same level or at most one level above in the tree generated by the traversal
in the connected graph every vertex will be seen because suppose there is a vertex that hasn't been seen. since the graph is connected there is a neighboring vertex
that connects to it. either that has been seen or it hasn't. if it hasn't then at then at some point there is a path leading from that neighbor to the start vertex
since the graph is connected. therefore the neighbor will eventually be seen an once the neighboring vertex is seen it's neighbors will be seen which include the unseen
vertex. every edge will be processed because suppose there is an edge that hasn't been processed. the origin vertex will eventually be seen as shown above. if the edge
hasn't been processed then either the destination vertex is processed in which case it's not in the queue but current vertex puts every neighbor vertex in the queue
hasn't been discovered. so the destination queue has a different discovering vertex that has processed the edge before (contradiction). therefore a condition of 
the current vertex being processed (not in the queue)
is that all outgoing edges to nodes that haven't been processed for the current vertex are processed. since this happens for every vertex every edge will be processed once.
 */
void bfs_1(int_graph *graph, int start, void (*process_before)(int), void (*process_edge)(int, int), void (*process_after)(int)) {
    setup_search(graph);
    terminate_search = 0;
    int_queue *queue = create_int_queue();
    enqueue(queue, start);
    discovered[start] = 1;
    int_edge *edges;
    int current;
    while (!is_empty(queue) && !terminate_search) {
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


void dfs_0(int_graph *graph, int start, void (*process_before)(int), void (*process_edge)(int, int), void (*process_after)(int)) {
    discovered[start] = 1;
    process_before(start);
    int_edge *edges = graph->vertices[start];
    int to;
    while (edges != NULL) {
        to = edges->to;
        if (!discovered[to]) {
            parents[to] = start;
            process_edge(start, to);
            dfs_0(graph, to, process_before, process_edge, process_after);
        }
        edges = edges->next;
    }
    process_after(start);
    processed[start] = 1;
    
}


/**
dfs traverses the edges of a connected component processing the edges that are formed from undiscovered neighbor nodes. the traversal
tree is formed branch by branch, subtree by subtree where tree edges to the next node are always undiscovered and left branches are formed first
right branches are formed only after no more undiscovered nodes can be used to form left branches and traversal tree returns from the level below in the
traversal tree
left subtrees are formed before right subtrees. dfs will process edges formed from undiscovered nodes and unprocessed nodes that are sitting on
the recursive call stack that are not the parent of the current node. I think these non tree nodes will only be processed if they are the destination
for edges in the same subtree at least 2 levels up in the traversal tree. if a vertex has been processed, then for the traversal node associated with the vertex,
all descendent nodes will have been processed (this is seen as a property of a stack). since the edges formed by
unprocessed non-parent (still in the recursive call stack) and undiscovered nodes are all processed for each node once,
every outgoing edge from any vertex and all of its descendents will be processed when
that vertex is processed (and popped from the recursive call stack). a processed node has all of its out-going edges and all of the out-going edges of its descendents processed.
another way to think of this is suppose there is an outgoing edge to a destination vertex that is not processed. this would imply that the destination vertex is undiscovered
in which case the current vertex is still in the call stack or the destination vertex is unprocessed in which case current vertex is above the destination in the call stack
in either case a condition for the current vertex to be popped off the call stack is for the edge formed by the current and destination vertex to be processed.
 */
void dfs_1(int_graph *graph, int start, void (*process_before)(int), void (*process_edge)(int, int), void (*process_after)(int)) {
    terminate_search = 0;
    discovered[start] = 1;
    process_before(start);
    int_edge *edges = graph->vertices[start];
    int neighbor;
    
    while (edges != NULL && !terminate_search) {
        neighbor = edges->to;
        if (!discovered[neighbor]) {
            parents[neighbor] = start;
            process_edge(start, neighbor);
            dfs_1(graph, neighbor, process_before, process_edge, process_after);
        }
        else if (!processed[neighbor] && parents[start] != neighbor || graph->is_directed) {
            process_edge(start, neighbor);
        }
        edges = edges->next;
    }
    process_after(start);
    processed[start] = 1;
}

void dfs_weighted(int_graph *graph, int start, void (*process_before)(int), void (*process_edge)(int, int, int), void (*process_after)(int)) {
    terminate_search = 0;
    discovered[start] = 1;
    process_before(start);
    int_edge *edges = graph->vertices[start];
    int neighbor;
    int weight;
    
    while (edges != NULL && !terminate_search) {
        neighbor = edges->to;
        weight = edges->weight;
        if (!discovered[neighbor]) {
            parents[neighbor] = start;
            process_edge(start, neighbor, weight);
            dfs_weighted(graph, neighbor, process_before, process_edge, process_after);
        }
        else if (!processed[neighbor] && parents[start] != neighbor || graph->is_directed) {
            process_edge(start, neighbor, weight);
        }
        edges = edges->next;
    }
    process_after(start);
    processed[start] = 1;
}

void find_path_bfs(int origin, int current, int child) {
    find_path(origin, current, child, parents);
}

void find_path(int origin, int current, int child, int parents[]) {
    if (current == origin) {
        if (child == -1) {
            printf("%d", current);
        }
        else {
            printf("(%d, %d)", current, child);
        }
    }
    else if (current == -1) {
        printf("could not find a path from %d", origin);
    }
    else {
        find_path(origin, parents[current], current, parents);
        if (child == -1) {
            printf("%d ", current);
            printf("\n");

        }
        else {
            printf("(%d, %d) ", current, child);
        }
    }
}

void print_connected(int_graph *graph, void (*process_before)(int), void (*process_edge)(int, int), void (*process_after)(int)) {
    setup_search(graph);
    int component = 0;
    for (int i = 1; i <= graph->num_vertices; i++) {
        if (!discovered[i]) {
            component++;
            printf("component %d\n", component);
            printf("\n");
            bfs_0(graph, i, process_before, process_edge, process_after);
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

adjacency_matrix *create_adjacency_matrix() {
    adjacency_matrix *matrix = malloc(sizeof(adjacency_matrix));
    return matrix;
}


adjacency_matrix *from_file_1(FILE *fp, int is_directed) {
    int num_vertices;
    int num_edges;
    int from;
    int to;
    int weight;
    
    fscanf(fp, "%d %d", &num_vertices, &num_edges);
    adjacency_matrix *matrix = create_adjacency_matrix();
    matrix->num_vertices = num_vertices;
    for (int i = 1; i <= matrix->num_vertices; i++) {
        for (int j = 1; j <= matrix->num_vertices; j++) {
            matrix->edge_weights[i][j] = INT32_MAX;
        }
    }
    
    int_graph *graph = create_int_graph(num_vertices, is_directed);

    while (fscanf(fp, "%d %d %d", &from, &to, &weight) != EOF) {
        matrix->edge_weights[from][to] = weight;
    }
    
    return matrix;
}

void show_matrix(adjacency_matrix *matrix) {
    for (int i = 1; i <= matrix->num_vertices; i++) {
        for (int j = 1; j <= matrix->num_vertices; j++) {
            if (matrix->edge_weights[i][j] != INT32_MAX) {
                printf("the edge (%d, %d) has weight %d\n", i, j, matrix->edge_weights[i][j]);
            }
        }
    }
}

int sum_degree(int *degrees, int num_vertices) {
    float sum = 0;
    for (int i = 0; i <= num_vertices; i++) {
        sum += degrees[i];
    }
    return sum;
}

color complement(color vertex_color) {
    switch (vertex_color) {
        case BLACK:
            return WHITE;
            break;
        case WHITE:
            return BLACK;
            break;
        default:
            return UNCOLORED;
    }
}

char *get_color(int vertex) {
    char *result;
    color vertex_color = colors[vertex];
    switch (vertex_color) {
        case BLACK:
            result = "BLACK";
            break;
        case WHITE:
            result = "WHITE";
            break;
        default:
            result = "UNCOLORED";
    }
    return result;
}

void process_color(int from, int to) {
    char *from_color = get_color(from);
    char *to_color = get_color(to);
    printf("the edge (%d, %d) before setting destination color is: (%s, %s)\n", from, to, from_color, to_color);
    if (colors[from] == colors[to]) {
        printf("graph is not bipartite\n");
        bipartite = 0;
        terminate_search = 1;
    }
    else {
        colors[to] = complement(colors[from]);
    }
    to_color = get_color(to);
    printf("the edge (%d, %d) after setting destination color is: (%s, %s)\n", from, to, from_color, to_color);

}

void show_color(int from) {
    char *result = get_color(from);
    printf("the vertex %d has color: %s\n", from, result);
    printf("\n");
}


int two_color(int_graph *graph) {
    bipartite = 1;

    for (int i = 1; i <= graph->num_vertices; i++) {
        colors[i] = UNCOLORED;
    }
    setup_search(graph);
    int start = 1;
    while (bipartite && start <= graph->num_vertices) {
        if (!discovered[start]) {
            colors[start] = WHITE;
            bfs_1(graph, start, show_color, process_color, show_color);
        }
    }
    return bipartite;
}

void show_cycle(int from, int to) {
    if (parents[to] != from) {
        printf("edge (%d,%d) forms a cycle with  along the path:\n", from, to);
        find_path(to, from, -1, parents);
        terminate_search = 1;
    }
    else {
        show_edge_type(from, to);
    }
}

void set_stack_level(int_graph *graph) {
    push_count = 0;
    pop_count = 0;
    last_push_index = -1;
    for (int i = 1; i <= graph->num_vertices; i++) {
        recursive_steps[i] = 0;

    }
}

void stack_level_before(int from) {
    last_push_index++;
    printf("the vertex %d is being processed in frame: %d\n",from, last_push_index);
}

void stack_level_after(int from) {
    last_push_index--;
    pop_count++;
    printf("the vertex %d is finished processing after %d pops from the call stack\n", from, pop_count);
}

void visit_node(int from) {
    last_push_index++;
    stack_indicies[from] = last_push_index;
    earliest_returns[from] = from;
}

void process_branch(int from, int to) {
    edge_type branch_type = edge_type_from(from, to);
    switch (branch_type) {
        case TREE:
            num_branches[from]++;
            break;
        case BACK:
            if (stack_indicies[to] < stack_indicies[earliest_returns[from]]) { //for all back edges for from vertex pick the one closest to root (earliest return)
                earliest_returns[from] = to;
            }
            break;
        case FORWARD:
            break;
        case CROSS:
            break;
        }
}

void leave_node(int from) {
    last_push_index--;
    if (stack_indicies[earliest_returns[from]] < stack_indicies[earliest_returns[parents[from]]]) {
        earliest_returns[parents[from]] = earliest_returns[from]; //ensures current node from will have earliest return of itself and all descendent nodes
    }

    if (parents[from] == - 1 && num_branches[from] > 1) {
        printf("root cut node at vertex: %d separates %d child nodes\n", from, num_branches[from]);
    }
    else if (parents[from] != -1 && parents[parents[from]] != -1) {
        if (earliest_returns[from] == parents[from]) {
            printf("the edge (%d, %d) has a parent cut node at vertex: %d\n", parents[from], from, parents[from]);
        }
        if (earliest_returns[from] == from) {
            printf("the edge (%d, %d) has a bridge cut node at vertex: %d\n", parents[from], from, parents[from]);
            if (num_branches[from] > 0) {
                printf("the bridge cut node at vertex: %d separates %d child nodes\n", from, num_branches[from]);
            }
        }

    }

}

void add_dependents_of(int required) {
    push(required_by, required);
}

void proper_dependents(int from, int to) {
    show_edge_type(from, to);
    if (edge_type_from(from, to) == BACK) {
        printf("warning graph is not a DAG and cannot be sorted!\n");
    }
}



void do_nothing(int from, int to) {}
void do_nothing_1(int from) {}


void setup_topo(int_graph *graph) {
    required_by = create_int_stack();
}

void topo_sort(int_graph *graph) {
    setup_topo(graph);
    for (int i = 1; i <= graph->num_vertices; i++) {
        if (!discovered[i]) {
            dfs_1(graph, i, process_node, proper_dependents, add_dependents_of);
        }
    }
}

void show_topo() {
    show_stack(required_by);
}

void process_node(int from) {
    visit_node(from);
    push_count++;
    recursive_steps[from] =  push_count;
}

int_graph *transpose(int_graph* graph) {
    int_graph *graph_transposed = create_int_graph(graph->num_vertices, 1);
    graph_transposed->is_directed = 1;
    int_edge *edges;
    int to;
    int weight;
    for (int from = 1; from <= graph->num_vertices; from++) {
        edges = graph->vertices[from];
        while (edges != NULL) {
            to = edges->to;
            weight = edges->weight;
            insert_edge(graph_transposed, to, from, weight, 1);
            edges = edges->next;
        }
    }
    return graph_transposed;
}

/**
the strategy for partitioning a directed graph into a set of strongly connected components is:
1. order the vertices in the reverse order in which they are processed using a stack. we can be assured
that for any vertex at the top of the stack there is a path from that vertex to any vertex below it in the stack.
2. construct the transpose graph and perform a dfs starting with vertex at the top of the previously constructed stack.
we can be assured that the first iteration will have the root of the dfs tree at the top of the stack for which there is a path
to every vertex below it in the stack. the dfs search on the transpose graph will find all vertices that have paths leading back to
the root in the original graph. (the rationale behind this is if there is a path from the vertex at the top of the stack to any other vertex in the transpose
graph, which have the edges reversed, then there is a path from that vertex to the vertex at the top of the stack in the original graph)
any vertex in this set of vertices will have a path to any other vertex in the set by traveling to the
root and from there traveling to the other vertex. so they are strongly connected. We need to be assured that the first vertex in the stack
that can't find a path to the root can find a path to the remaining vertices that haven't been discovered by the previous dfs search
(we would like to know that graph can be partitioned by connected components, I think this is obvious but it must not have been when I wrote this)
that in turn can discover this vertex. We can be assured that the set of vertices that have a path to this next vertex will lie below 
it on the stack
because if it didn't it would lie above it on the stack in the group of vertices that have path's to the root. therefore there is a path
from the vertex to the set of vertices for which there is a path to the vertex since the set of vertices lie below the vertex in the stack.
this argument is can be repeated until the stack is empty giving a full partition of strong connected components of a directed graph.
the code basically says from those the vertex "from" can find, find every vertex "to" that can find "from"
 */

void process_connected_after(int from) {
    printf("the vertex %d for the tree edge (%d, %d) is processed\n", from, parents[from], from);
    add_dependents_of(from);
}







void strongly_connected(int_graph *graph) {
    setup_search(graph);
    setup_topo(graph);
    for (int start = 1; start <= graph->num_vertices; start++) {
        if (!discovered[start]) {
            dfs_1(graph, start, show_vertex_before, do_nothing, process_connected_after);
        }
    }

    int_graph *graph_transposed = transpose(graph);
    setup_search(graph_transposed);
    int component = 0;
    while (not_empty(required_by)) {
        int required = pop(required_by);
        if (!discovered[required]) {
            component++;
            printf("strongly connected component %d of original graph with start of %d\n", component, required);
            dfs_1(graph_transposed, required, show_vertex_before, show_edge, show_vertex_after);
            printf("\n");
        }
    }

    
}

int prims_algo(int_graph *graph, int start) {
    int is_tree_vertex[MAX_VERTICES + 1];
    int weights[MAX_VERTICES + 1];
    int parents[MAX_VERTICES + 1];

    int total_weight = 0;
    int min_weight = 0;
    int current;
    int_edge *edges;
    int dest_vertex;
    for (int i = 1; i <= graph->num_vertices; i++) {
        weights[i] = INT32_MAX;
        is_tree_vertex[i] = 0;
        parents[i] = -1;
    }

    current = start;
    while (!is_tree_vertex[current]) {
        total_weight += min_weight;
        is_tree_vertex[current] = 1;
        printf("the edge (%d, %d) is an edge in the minimum spanning tree\n", parents[current], current);
        edges = graph->vertices[current];
        //keep track of edge weight of all non-tree vertices and the current tree vertex that they form an edge with
        //if the edge weight of the edge connecting them is smaller than a known edge weight to the non-tree vertex
        while (edges != NULL) {
            dest_vertex = edges->to;
            if (!is_tree_vertex[dest_vertex] && weights[dest_vertex] > edges->weight) {
                parents[dest_vertex] = current;
                weights[dest_vertex] = edges->weight;
            }
            edges = edges->next;
        }

        //select the next non tree vertex that has minimum edge weight
        //we can be assured that it forms an edge with a tree vertex because if it didn't then it's edge weight would be the default INT32_MAX
        //assuming every edge in the graph has weight less than INT32_MAX and isn't equally weighted this would imply that the current vertex
        // had no outgoing edges
        //either the current vertex is the first tree vertex or it isn't. if it is, this would imply that the graph is disconnected so no
        //point in finding a spanning tree let alone a minimum one. if it isn't, this would imply that all previous tree vertices have
        //outgoing edge weights of INT32_MAX which violates assumption.
        min_weight = INT32_MAX;
        for (int i = 1; i <= graph->num_vertices; i++) {
            if (!is_tree_vertex[i] && weights[i] < min_weight) {
                current = i;
                min_weight = weights[i];
            }
        }

    }
    return total_weight;
}


int dijkstra(int_graph *graph, int start) {
    int is_tree_vertex[MAX_VERTICES + 1];
    int weights[MAX_VERTICES + 1];
    int parents[MAX_VERTICES + 1];

    int total_weight = 0;
    int min_weight = 0;

    int current;
    int_edge *edges;
    int dest_vertex;

    for (int i = 1; i <= graph->num_vertices; i++) {
        is_tree_vertex[i] = 0;
        weights[i] = INT32_MAX;
        parents[i] = -1;
    }

    current = start;
    weights[current] = 0;

    while (!is_tree_vertex[current]) {
        is_tree_vertex[current] = 1;
        printf("edge (%d, %d) is an edge in the tree minimizing sum of edges weights in the path from vertex %d to every other vertex in the tree\n", parents[current], current, start);
        total_weight += min_weight;
        edges = graph->vertices[current];
        while (edges != NULL) {
            dest_vertex = edges->to;
            if (!is_tree_vertex[dest_vertex] && weights[dest_vertex] > weights[current] + edges->weight) {
                parents[dest_vertex] = current;
                weights[dest_vertex] = weights[current] + edges->weight;
            }
            edges = edges->next;
        }

        min_weight = INT32_MAX;
        for (int i = 1; i <= graph->num_vertices; i++) {
            if (!is_tree_vertex[i] && weights[i] < min_weight) {
                current = i;
                min_weight = weights[i];
            }
        }
    }
    return total_weight;
}

void setup_collect_edges(int_graph *graph) {
    in_offset = 1;
}

void collect_edges(int from, int to, int weight) {
    edge_pair pair = {.vertex_1 = from, .vertex_2 = to, .weight = weight};
    edges[in_offset] = pair;
    in_offset++;
}

edge_pair *edge_pairs_from(int_graph *graph, int start) {
    setup_collect_edges(graph);
    dfs_weighted(graph, start, do_nothing_1, collect_edges, do_nothing_1);
    return edges;
}

edge_pair *edge_pairs_from_v1(int_graph *graph) {

    int finished_outgoing[MAX_VERTICES + 1];
    for (int i = 1; i <= graph->num_vertices; i++) {
        finished_outgoing[i] = 0;
    }

    edge_pair *edge_pairs = calloc(graph->num_edges + 1, sizeof(edge_pair));
    int in_offset = 1;

    int_edge *edges;
    int to;
    int weight;

    for (int i = 1; i <= graph->num_vertices; i++) {
        edges = graph->vertices[i];
        while (edges != NULL) {
            to = edges->to;
            weight = edges->weight;
            if (!finished_outgoing[to]) {
                edge_pair pair = {.vertex_1 = i, .vertex_2 = to, weight};
                edge_pairs[in_offset] = pair;
                in_offset++;
            }
        }
        finished_outgoing[i] = 1;
    }
    return edge_pairs;
}

int compare_weight(const void *ep_1, const void *ep_2) {
    edge_pair *pair_1 = (edge_pair *) ep_1;
    edge_pair *pair_2 = (edge_pair *) ep_2;

    if (pair_1->weight < pair_2->weight) {
        return -1;
    }
    else if (pair_1->weight > pair_2->weight) {
        return 1;
    }
    else {
        return 0;
    }
}

union_find *create_union_find() {
    union_find *set = malloc(sizeof(union_find));
    return set;
}


void setup_union_find(union_find *set, int num_partitions) {
    for (int i = 1; i <= num_partitions; i++) {
        set->parents[i] = i; //initially we start with every vertex having its own partition and being its own parent for num_partitions = num_vertices
        set->component_partition_size[i] = 1;
    }
    set->num_partitions = num_partitions;

}

int find_partition(union_find *set, int of) {
    if (set->parents[of] == of) {
        return of;
    }
    else {
        return find_partition(set, set->parents[of]);
    }
}

void merge_partitions(union_find *set, int e1, int e2) {
    int r1 = find_partition(set, e1);
    int r2 = find_partition(set, e2);
    if (r1 != r2) {
        if (set->component_partition_size[r1] >= set->component_partition_size[r2]) {
            set->component_partition_size[r1] += set->component_partition_size[r2];
            set->parents[r2] = r1;
        }
        else {
            set->component_partition_size[r2] += set->component_partition_size[r1];
            set->parents[r1] = r2;
        }
    }
}

int same_component(union_find *set, int vertex_1, int vertex_2) {
    int r1 = find_partition(set, vertex_1);
    int r2 = find_partition(set, vertex_2);
    return find_partition(set, vertex_1) == find_partition(set, vertex_2); 
}

/**
this algorithm starts with a num_vertices partitions each forming its own component labeled with the key that is the same as
the key of the vertex contained in the component. we can be assured each "component" is disjoint and has a minimal edge weight of 0
each partition can be merged only if there is a subset of the num_edges edges connecting any two vertices in them. (this subset forms 
a path between 2 vertices)
since the edges are selected in order of increasing weight we can be assured that for each path prefix contained in one component the marginal
increase in the weight of a path formed by the path prefix and the edge(s) needed to connect to a vertex in another component is minimal.
since the original graph is connected (a given) we can be assured that by sweeping through all edges and merging partitions for edges formed by
vertices between 2 disjoint components must yield a partition that contains all vertices because for any two vertices in a connected graph there
must be a subset of num_edges edges that connects them. we can be assured that for any component that that makes up a partition the set of edges
that were used to form that partition has minimal weight sum because the marginal edge weight increase of adding another vertex to the 
partition is minimal (it was the first one in an ascending ordered list of edges by weight that could be used to merge them).
therefore the partition containing all of the vertices is formed by disjoint partitions representing the minimal spanning tree for the subset
of vertices contained in each partition and an edge with the smallest weight that can be used to connect a vertex of one component with another.
therefore joining any two components maintains a partition that represents the minimal spanning tree for the union of the vertices in both 
components.
(Note the proof is shaky but is plausible enough for me.)
the algorithm basically filters out the edges with the smallest edge weights that can be used to form a spanning tree of the original graph by
first sorting them and then selecting edges using the predicate that the vertices that form the edges are not in the same component.
quite nifty if you ask me.
 */

int kruskal(int_graph *graph) {
    union_find *set = create_union_find();
    setup_union_find(set, graph->num_vertices);
    edge_pair *pairs = edge_pairs_from(graph, 1);
    qsort(pairs, graph->num_edges, sizeof(edge_pair), compare_weight);
    edge_pair pair;
    int total_weight = 0;
    for (int i = 1; i <= graph->num_edges; i++) {
        pair = pairs[i];
        if (!same_component(set, pair.vertex_1, pair.vertex_2)) {
            printf("the edge (%d, %d) was added to the minimal spanning tree\n", pair.vertex_1, pair.vertex_2);
            merge_partitions(set, pair.vertex_1, pair.vertex_2);
            total_weight += pair.weight;
        }
    }
    return total_weight;
} 

/**
suppose v_1,v_2...v_n are the sequence of vertices forming the path with minimal sum of edge weight
between v_1 and v_n. every path prefix must also have minimal sum of edge weights between it two endpoints because if it didn't
we could also find a smaller edge weight sum by subbing in vertices
that form edges with smaller edge weight. so we have a set of path prefixes with minimal sum of edge weights
((v_1), (v_1, v_2), (v_1, v_2, v_3),.....,(v1,..,v_n-2,v_n-1), (v1,..,v_n_1, v_n)) where each successive prefix is equal to
the previous prefix plus one additional vertex that forms an edge between the last entry in the previous sequence. for any two
vertices the following algorithm will find the vertex through which the sum of the paths edge weights joining the two vertices will be as
small as possible if it can, and update the corresponding entry in the matrix for those two vertices with that weight.
this means v_2 will be found for (v_1, v_3), v_3 for (v_2,v_4),....v_(n - 1) for (v_(n - 2), v_n). so for ex. the entry for (v_1, v_3)
will have value w(v_1, v_2) + w(v_2, v_3) so what about (v_1,v_4) the below algorithm will search for the vertex connecting them that minimizes
the sum of edge weights and it will find v_3 with weight value w(v_1, v_2) + w(v_2, v_3). the entry for (v_1, v_4)
will be updated to the value w(v_1, v_3) + w(v_3,v_4) =  w(v_1, v_2) + w(v_2, v_3) + w(v_3,v_4). I think this is how minimum edge weight for
a path between any 2 vertices are propagated
throughout the iterations of the algorithm. this is the best explanation I can think of and it's semi plausible
(basically if a previous updated entry (i,j) is used to calculate w(i, j) + w(j, j') where w(i,j) = w(i,k) + w(k,j) then this
is how we can use multiple "possible intermediate vertices" in the path from (i, j')) 
 */

void floyd(adjacency_matrix *matrix) {
    int detour_weight;
    for(int k = 1; k <= matrix->num_vertices; k++) {
        for (int i = 1; i <= matrix->num_vertices; i++) {
            for (int j = 1; j <= matrix->num_vertices; j++) {
                detour_weight = matrix->edge_weights[i][k] + matrix->edge_weights[k][j];
                if (detour_weight < matrix->edge_weights[i][j]) {
                    matrix->edge_weights[i][j] = detour_weight;
                }
            }
        }
    }
}



