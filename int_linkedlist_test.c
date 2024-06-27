#include <stdlib.h>
#include <stdio.h>
#include "my_types.h"

int_list_node *create_node(int data);
void insert_front(int_list_node **ns, int data);
int_list_node *search(int_list_node *start, int data);
void delete_node(int_list_node **start, int_list_node *n);
void show_int_list(int_list_node *ns);


int main(void) {
    int_list_node *ns = create_node(5);
    insert_front(&ns, 4);
    insert_front(&ns, 3);
    insert_front(&ns, 2);
    insert_front(&ns, 1);
    show_int_list(ns);
    int_list_node *three = search(ns, 3);
    printf("searching for existing element yields: %d\n", three->data);
    int_list_node *dne = search(ns, 0);
    printf("searching for nonexistent node yeilds: %p\n", dne);
    delete_node(&ns, three);
    printf("after deleting the number three we have:\n");
    show_int_list(ns);
    free(ns);
}