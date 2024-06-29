struct int_tree_node {
    int data;
    struct int_tree_node *parent;
    struct int_tree_node *left;
    struct int_tree_node *right;

};

typedef struct int_tree_node int_tree_node;

int_tree_node *create_node(int data);
void insert(int_tree_node **start, int_tree_node *parent, int data);
int_tree_node *minimum(int_tree_node *start);
int_tree_node *successor(int_tree_node *of);
void delete_node(int_tree_node **start, int_tree_node *parent, int_tree_node *target);
int_tree_node *search(int_tree_node *start, int data);
void show(int_tree_node *ns, int ns_length);