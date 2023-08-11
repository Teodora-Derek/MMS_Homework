#include <stdio.h>
#include <stdlib.h>

#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H 1

typedef struct Data
{
    int num;
} Data;

typedef struct Node
{
    Data data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct LinkedList
{
    Node *tail;
    Node *head;
    size_t cur_elem_count;
} LinkedList;

LinkedList *init_linked_list();
int pop_front(LinkedList *linked_list, Data *result);
int push_front(LinkedList *linked_list, Data data);
int push_back(LinkedList *linked_list, Data data);
int pop_back(LinkedList *linked_list, Data *result);
void print_linked_list(LinkedList linked_list);
void deinit_linked_list(LinkedList *linked_list);

#endif