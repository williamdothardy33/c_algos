#include <stdio.h>
#include <stdlib.h>
#include "my_types.h"

int_tree_node *create_node(int data);
void insert(int_tree_node **start, int_tree_node *parent, int data);
int_tree_node *minimum(int_tree_node *start);
int_tree_node *successor(int_tree_node *of);
void delete(int_tree_node **start, int_tree_node *parent, int_tree_node *target);
int_tree_node *search(int_tree_node *start, int data);
void show(int_tree_node *ns, int ns_length);

int main(void) {
    printf("creating root\n");
    int_tree_node *root = create_node(4);
    printf("root is: %d\n", root->data);
    printf("inserting 2...\n");
    insert(&root, NULL, 2);
    printf("left of root after inserting 2 is %d\n", root->left->data);
    printf("inserting 7...\n");
    insert(&root, NULL, 7);
    printf("right of root after inserting 7 is %d\n", root->right->data);
    insert(&root, NULL, 5);
    insert(&root, NULL, 8);
    insert(&root, NULL, 1);
    show(root, 6);

    printf("\n");
    printf("deleting 2...\n");
    int_tree_node *two = root->left;
    delete(&root, NULL, two);
    printf("show after delete\n");
    printf("root is now: %d\n", root->data);
    printf("left of root is now: %d\n", root->left->data);
    printf("right of root is now: %d\n", root->right->data);
    show(root, 5);

    printf("\n");
    printf("deleting 8...\n");
    int_tree_node *eight = root->right->right;
    delete(&root, NULL, eight);
    printf("show after delete\n");
    printf("root is now: %d\n", root->data);
    printf("left of root is now: %d\n", root->left->data);
    printf("right of root is now: %d\n", root->right->data);
    show(root, 4);


    printf("\n");
    printf("deleting 4...\n");
    int_tree_node *four = root;
    delete(&root, NULL, four);
    printf("show after delete\n");
    printf("root is now: %d\n", root->data);
    printf("left of root is now: %d\n", root->left->data);
    printf("right of root is now: %d\n", root->right->data);
    show(root, 3);

    int_tree_node *seven = search(root, 7);
    printf("searching for an existing value 7 yields %d\n", seven->data);
    int_tree_node *dne = search(root, 10);
    printf("searching for non existing value 10 yeilds %p\n", dne);
}