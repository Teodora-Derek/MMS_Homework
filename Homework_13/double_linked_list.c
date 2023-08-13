#include "double_linked_list.h"

LinkedList *init_linked_list()
{
    LinkedList *linked_list = malloc(sizeof(*linked_list));
    linked_list->cur_elem_count = 0;
    linked_list->is_dissposed = 0;
    return linked_list;
}

int push_front(LinkedList *linked_list, void *data)
{
    if (!linked_list)
        return 1;

    Node *new_node = malloc(sizeof(*new_node));
    new_node->data = data;

    if (linked_list->cur_elem_count == 0)
    {
        linked_list->head = new_node;
        linked_list->tail = new_node;
        new_node->prev = NULL;
        new_node->next = NULL;
    }
    else
    {
        new_node->next = linked_list->head;
        new_node->prev = NULL;
        linked_list->head->prev = new_node;
        linked_list->head = new_node;
    }
    linked_list->cur_elem_count++;
    return 0;
}

int push_back(LinkedList *linked_list, void *data)
{
    if (!linked_list)
        return -1;

    Node *new_node = malloc(sizeof(*new_node));
    new_node->data = data;

    if (linked_list->cur_elem_count == 0)
    {
        linked_list->head = new_node;
        linked_list->tail = new_node;
        new_node->next = NULL;
        new_node->prev = NULL;
    }
    else
    {
        new_node->prev = linked_list->tail;
        new_node->next = NULL;
        linked_list->tail->next = new_node;
        linked_list->tail = new_node;
    }
    linked_list->cur_elem_count++;
    return 0;
}

void *pop_front(LinkedList *linked_list)
{
    if (!linked_list || linked_list->cur_elem_count == 0)
        return NULL;

    void *result = linked_list->head->data;
    Node *head = linked_list->head;

    if (linked_list->head == linked_list->tail)
    {
        linked_list->head = NULL;
        linked_list->tail = NULL;
    }
    else
    {
        linked_list->head = linked_list->head->next;
        linked_list->head->prev = NULL;
        head->next = NULL;
    }
    free(head);
    linked_list->cur_elem_count--;

    return result;
}

void *pop_back(LinkedList *linked_list)
{
    if (!linked_list || linked_list->cur_elem_count == 0)
        return NULL;

    void *result = linked_list->tail->data;
    Node *tail = linked_list->tail;

    if (linked_list->head == linked_list->tail)
    {
        linked_list->tail = NULL;
        linked_list->head = NULL;
    }
    else
    {
        linked_list->tail = linked_list->tail->prev;
        linked_list->tail->next = NULL;
        tail->prev = NULL;
    }
    free(tail);
    linked_list->cur_elem_count--;

    return result;
}

void print_linked_list(LinkedList *linked_list, void (*print_func)(void *))
{
    if (!linked_list || linked_list->is_dissposed)
    {
        printf("The linkedlist is already disposed and does not exist!\n");
        return;
    }

    for (Node *curr = linked_list->head; curr != NULL; curr = curr->next)
        print_func(curr->data);
    printf("\n");
}

void deinit_linked_list(LinkedList *linked_list)
{
    if (!linked_list)
        return;

    Node *head = linked_list->head;
    while (head)
    {
        Node *curr = head;
        head = head->next;
        free(curr->data);
        free(curr);
    }
    free(head);
    head = NULL;

    linked_list->is_dissposed = 1;
    free(linked_list);
}
