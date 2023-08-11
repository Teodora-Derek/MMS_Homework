#include "deque.h"

Deque *init_deque()
{
    return init_linked_list();
}

int insertFront(Deque *deque, Data data)
{
    return push_front(deque, data);
}

int insertRear(Deque *deque, Data data)
{
    return push_back(deque, data);
}

int deleteFront(Deque *deque, Data *result)
{
    return pop_front(deque, result);
}

int deleteRear(Deque *deque, Data *result)
{
    return pop_back(deque, result);
}

void print_deque(Deque deque)
{
    print_linked_list(deque);
}

void deinit_deque(Deque *deque)
{
    deinit_linked_list(deque);
}