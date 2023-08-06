#include "double_linked_list.h"

#ifndef DEQUE_H
#define DEQUE_H 2

typedef LinkedList Deque;

Deque *init_deque();
int insertFront(Deque *deque, Data data);
int insertRear(Deque *deque, Data data);
int deleteFront(Deque *deque, Data *result);
int deleteRear(Deque *deque, Data *result); 
void print_deque(Deque deque);
void deinit_deque(Deque *deque);

#endif