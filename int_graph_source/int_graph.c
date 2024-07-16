#include "int_graph.h"
#include <stdlib.h>
#include <time.h>
#include "../int_queue_source/int_queue.h"
#include "../int_stack_source_v2/int_stack.h"

int terminate_search;
int push_count;
int last_push_index;
int pop_count;
color colors[MAX_VERTICES + 1];
int bipartite;
int num_branches[MAX_VERTICES + 1];
int stack_indicies[MAX_VERTICES + 1];
int earliest_returns[MAX_VERTICES + 1];
int discovered[MAX_VERTICES + 1], processed[MAX_VERTICES + 1], parents[MAX_VERTICES + 1];

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

edge_type edge_type_from(int from, int to, int discovered[], int processed[], int parents[]) {
    if (!discovered[to] || parents[to] == from) {
        return TREE;
    }
    else if (discovered[to] && !processed[to]) {
        return BACK;
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
void show_edge_type(int from, int to) {
    edge_type type = edge_type_from(from, to, discovered, processed, parents);
    char *result;
    switch (type) {
        case TREE:
            result = "TREE";
            break;
        case BACK:
            result = "BACK";
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

void set_stack_level() {
    push_count = 0;
    pop_count = 0;
    last_push_index = -1;
}

void stack_level_before(int from) {
    push_count++;
    printf("the vertex %d is being processed in frame: %d\n",from, push_count);
}

void stack_level_after(int from) {
    push_count--;
    pop_count++;
    printf("the vertex %d is finished processing after %d pops from the call stack\n", from, pop_count);
}

void visit_node(int from) {
    last_push_index++;
    stack_indicies[from] = last_push_index;
    earliest_returns[from] = from;
}

void process_branch(int from, int to) {
    edge_type branch_type = edge_type_from(from, to, discovered, processed, parents);
    switch (branch_type) {
        case TREE:
            num_branches[from]++;
            break;
        case BACK:
            if (stack_indicies[to] < stack_indicies[earliest_returns[from]]) { //for all back edges for from vertex pick the one closest to root (earliest return)
                earliest_returns[from] = to;
            }
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