#include "double_linked_list.h"

#ifndef STACK_H
#define STACK_H 1

typedef LinkedList Stack;

Stack *init_stack();
int push(Stack *stack, void *data);
void *pop(Stack *stack);
void print_stack(Stack *stack, void (*print_func)(void *));
void deinit_stack(Stack *stack);

#endif
