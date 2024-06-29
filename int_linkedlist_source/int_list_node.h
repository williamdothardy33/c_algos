#include <stdio.h>
struct int_list_node {
    int data;
    struct int_list_node *next;
};

typedef struct int_list_node int_list_node;

int_list_node *create_node(int data);
void insert_front(int_list_node **ns, int data);
int_list_node *search(int_list_node *start, int data);
void delete_node(int_list_node **start, int_list_node *n);
void show_int_list(int_list_node *ns);
void reverse(int_list_node **ns);