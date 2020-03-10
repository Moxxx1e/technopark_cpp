#ifndef LIST_H
#define LIST_H

#include "header.h"

typedef struct Node
{
    char* string;
    struct Node* next;
} Node;

Node* create_node(char* string);

Node* append_to_list(Node* head, Node* new_element);

int list_size(Node* head);

void print_list(Node* head);

void free_list(Node* head);

#endif // LIST_H
