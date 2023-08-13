#include "deque.h"

Deque *init_deque()
{
    return init_linked_list();
}

int insertFront(Deque *deque, void *data)
{
    return push_front(deque, data);
}

int insertRear(Deque *deque, void *data)
{
    return push_back(deque, data);
}

void *deleteFront(Deque *deque)
{
    return pop_front(deque);
}

void *deleteRear(Deque *deque)
{
    return pop_back(deque);
}

void print_deque(Deque *deque, void (*print_func)(void *))
{
    print_linked_list(deque, print_func);
}

void deinit_deque(Deque *deque)
{
    deinit_linked_list(deque);
}