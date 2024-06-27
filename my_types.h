struct int_list_node {
    int data;
    struct int_list_node *next;
};

typedef struct int_list_node int_list_node;

struct int_tree_node {
    int data;
    struct int_tree_node *parent;
    struct int_tree_node *left;
    struct int_tree_node *right;

};

typedef struct int_tree_node int_tree_node;