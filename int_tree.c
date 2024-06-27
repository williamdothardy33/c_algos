#include <stdio.h>
#include <stdlib.h>
#include "my_types.h"

int_tree_node *create_node(int data) {
    int_tree_node *ns = malloc(sizeof(int_tree_node));
    ns->data = data;
    ns->parent = NULL;
    ns->left = NULL;
    ns->right = NULL;
    return ns;
}

void insert(int_tree_node **start, int_tree_node *parent, int data) {
    if (*start == NULL) {
        int_tree_node *new_leaf = create_node(data);
        if (parent != NULL) {
            new_leaf->parent = parent;
        }
        *start = new_leaf;
    }
    else {
        int_tree_node *current = *start;
        if (data < current->data) {
            insert(&(current->left), current, data);
        }
        else {
            insert(&(current->right), current, data);
        }
    }
}

int_tree_node *minimum(int_tree_node *start) {
    if (start == NULL || start->left == NULL) {
        return start;
    }
    else {
        return minimum(start->left);
    }
}

int_tree_node *successor(int_tree_node *of) {
    int_tree_node *result = NULL;
    if (of != NULL) {
        result = minimum(of->right);
    }
    return result;
}

/*void delete(int_tree_node **start, int_tree_node *parent, int_tree_node *target) {
    int_tree_node *current = *start;
    if (current == target) {
        if (current->left == NULL && current->right == NULL) {
            *start = NULL;
        }
        else if (current->left != NULL && current->right == NULL) {
            *start = current->left;
            current->left->parent = parent;
            free(current);

        }
        else if (current->left == NULL && current->right != NULL) {
            *start = current->right;
            current->right->parent = parent;
            free(current);
        }
        else {
            int_tree_node *successor_node = successor(current);
            current->data = successor_node->data;
            delete(&successor_node, current, successor_node);
        }
    }
    else {
        if (target->data < current->data) {
            delete(&(current->left), current, target);
        }
        else {
            delete(&(current->right), current, target);
        }
    }
}*/

void delete(int_tree_node **start, int_tree_node *parent, int_tree_node *target) {
    int_tree_node *current = *start;
    if (current != NULL) {
        if (current == target) {
            int_tree_node *successor_node = successor(current);
            if (successor_node != NULL) {
                if (current->right != successor_node) {
                    current->data = successor_node->data;
                    delete(&current->right, current, successor_node);
                }
                else {
                    *start = current->right;
                    current->right->parent = parent;
                    free(current);
                }
            }
            else {
                *start = current->left;
                if (current->left != NULL) {
                    current->left->parent = parent;
                }
                free(current);

            }
        }
        else {
            if (target->data < current->data) {
                delete(&(current->left), current, target);
            }
            else {
                delete(&(current->right), current, target);
            }
        }
    
    }
}

int_tree_node *search(int_tree_node *start, int data) {
    int_tree_node *current = start;
    if (current == NULL || current->data == data) {
        return current;
    }
    else {
        if (data < current->data) {
            return search(current->left, data);
        }
        else {
            return search(current->right, data);
        }
    }
}

void show(int_tree_node *ns, int ns_length) {
    int_tree_node *queue[ns_length];
    queue[0] = ns;
    int queue_idx = 0;
    int next_idx = 0;
    
    while (next_idx < ns_length && queue_idx < ns_length) {
        int_tree_node *current = queue[next_idx];
        if (current != NULL) {
            if (current->left != NULL) {
                queue_idx += 1;
                queue[queue_idx] = current->left;
            }
            if (current->right != NULL) {
                queue_idx += 1;
                queue[queue_idx] = current->right;
            }
        }
        next_idx += 1;
    }

    int print_idx = 0;
    while (print_idx < ns_length) {
        printf("node %d has parent %d\n", queue[print_idx]->data, queue[print_idx]->parent != NULL ? queue[print_idx]->parent->data: 0);
        print_idx += 1;
    }

}