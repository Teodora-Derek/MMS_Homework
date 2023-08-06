#include "double_linked_list.h"

LinkedList *init_linked_list()
{
    LinkedList *linked_list = malloc(sizeof(*linked_list));
    linked_list->cur_elem_count = 0;
    return linked_list;
}

int push_front(LinkedList *linked_list, Data data)
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
        return 0;
    }

    linked_list->head->prev = new_node;
    new_node->next = linked_list->head;
    linked_list->head = new_node;
    linked_list->cur_elem_count++;
    return 0;
}

int pop_front(LinkedList *linked_list, Data *result)
{
    if (!linked_list || linked_list->cur_elem_count == 0)
        return 1;

    if (result)
        *result = linked_list->head->data;

    Node *head = linked_list->head;
    linked_list->head = linked_list->head->next;
    head->next = NULL;
    linked_list->head->prev = NULL;

    free(head);
    linked_list->cur_elem_count--;
    return 0;
}

int push_back(LinkedList *linked_list, Data data)
{
    if (!linked_list)
        return -1;

    if (linked_list->cur_elem_count == 0)
    {
        linked_list->head = malloc(sizeof(*(linked_list->head)));
        linked_list->head->data = data;
        linked_list->head->prev = NULL;
        linked_list->head->next = NULL;
        linked_list->tail = linked_list->head;
        linked_list->cur_elem_count++;
        return 0;
    }

    Node *new_node = malloc(sizeof(*new_node));
    new_node->data = data;
    new_node->prev = linked_list->tail;
    new_node->next = NULL;

    linked_list->tail->next = new_node;
    linked_list->tail = new_node;
    linked_list->cur_elem_count++;
    return 0;
}

int pop_back(LinkedList *linked_list, Data *result)
{
    if (linked_list->cur_elem_count == 0)
        return -1;

    if (result) // if the result is not NULL
        *result = linked_list->tail->data;

    Node *tail = linked_list->tail;
    *result = tail->data;
    linked_list->tail = tail->prev;
    tail->prev = NULL;
    linked_list->tail->next = NULL;
    free(tail);

    if (linked_list->tail == NULL)
        linked_list->head = NULL;

    linked_list->cur_elem_count--;
    return 0;
}

void print_linked_list(LinkedList linked_list)
{
    for (Node *curr = linked_list.head; curr != NULL; curr = curr->next)
        printf("%d ", curr->data.num);
    printf("\n");
}

void deinit_linked_list(LinkedList *linked_list)
{
    Node *curr = linked_list->head;
    while (curr)
    {
        pop_front(linked_list, NULL);
        curr = linked_list->head;
    }

    free(linked_list);
}
