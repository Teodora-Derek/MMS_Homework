#include "stack.h"

Stack *init_stack()
{
    return init_linked_list();
}

int push(Stack *stack, void *data)
{
    return push_front(stack, data);
}

void *pop(Stack *stack)
{
    return pop_front(stack);
}

void print_stack(Stack *stack, void (*print_func)(void *))
{
    return print_linked_list(stack, print_func);
}

void deinit_stack(Stack *stack)
{
    return deinit_linked_list(stack);
}