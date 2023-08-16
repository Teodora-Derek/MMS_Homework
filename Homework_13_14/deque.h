#include "double_linked_list.h"

#ifndef DEQUE_H
#define DEQUE_H 2

typedef LinkedList Deque;

Deque *init_deque();
int insertFront(Deque *deque, void *data);
int insertRear(Deque *deque, void *data);
void *deleteFront(Deque *deque);
void *deleteRear(Deque *deque);
void print_deque(Deque *deque, void (*print_func)(void *));
void deinit_deque(Deque *deque);

#endif
