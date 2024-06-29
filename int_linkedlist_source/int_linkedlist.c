#include <stdio.h>
#include <stdlib.h>
#include "int_list_node.h"

int_list_node *create_node(int data) {
    int_list_node *ns = malloc(sizeof(int_list_node));
    ns->data = data;
    ns->next = NULL;

    return ns;
}

void insert_front(int_list_node **ns, int data) {
    int_list_node *new_head = create_node(data);
    new_head->next = *ns;
    *ns = new_head;
}

int_list_node *search(int_list_node *start, int data) {
    int_list_node *current = start;
    int_list_node *result = NULL;
    while (current != NULL) {
        if (current->data == data) {
            result = current;
            break;
        }
        current = current->next;
    }

    return result;
}

void delete_node(int_list_node **start, int_list_node *n) {
    int_list_node *previous = NULL;
    int_list_node *current = *start;
    while (current != NULL) {
        if (current == n) {
            if (previous == NULL) {
                *start = current->next;
            }
            else {
                previous->next = current->next;
            }
            free(current);
            break;
        }
        else {
            previous = current;
            current = current->next;
        }
    }
}

void show_int_list(int_list_node *ns) {
    printf("[");
    int_list_node *current = ns;
    while (current != NULL) {
        if (current->next == NULL) {
            printf("%d", current->data);
            break;
        }
        else {
            printf("%d, ", current->data);
        }
        current = current->next;
    }
    printf("]\n");
}

void reverse(int_list_node **ns) {
    int_list_node *current = *ns;
    if (current != NULL && current->next != NULL) {
        int_list_node *next = current->next;
        current->next = NULL;
        while (next != NULL) {
            int_list_node *after_next = next->next;
            next->next = current;
            *ns = next;
            current = next;
            next = after_next;
        }
    }
}


