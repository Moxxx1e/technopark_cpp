#include "list.h"

Node* create_node(char* string)
{
    Node* element = (Node*)malloc(sizeof(Node));

    if (element)
    {
        element->string = string;
        element->next = NULL;
    }
    return element;
}

Node* append_to_list(Node* head, Node* new_element)
{
    if (!head)
    {
        return new_element;
    }

    Node* cur = head;

    for (; cur->next; cur = cur->next);

    cur->next = new_element;

    return head;
}

void free_list(Node* head)
{
    Node* next;
    for(; head; head = next)
    {
        next = head->next;
        free(head);
    }
}

void print_list(Node* head)
{
    Node* cur = head;
    for( ;cur; cur = cur->next)
    {
        fprintf(TMP_OUT_FILE, "%s", cur->string);
    }
}

int list_size(Node* head)
{
    Node* cur = head;
    int count = 0;
    for(; cur; cur = cur->next)
    {
        count++;
    }
    return count;
}
