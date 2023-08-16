#include <stdio.h>
#include <stdlib.h>

#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H 1

typedef struct Node
{
    void *data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct LinkedList
{
    Node *tail;
    Node *head;
    size_t cur_elem_count;
    size_t is_disposed;
} LinkedList;

LinkedList *init_linked_list();
int push_front(LinkedList *linked_list, void *data);
int push_back(LinkedList *linked_list, void *data);
void *pop_front(LinkedList *linked_list);
void *pop_back(LinkedList *linked_list);
void print_linked_list(LinkedList *linked_list, void (*print_func)(void *));
void deinit_linked_list(LinkedList *linked_list);

// sort the linked_list using custom cmp
void sort_linked_list(LinkedList *linked_list, int (*cmp)(const void *, const void *));
#endif
