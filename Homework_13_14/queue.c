#include "./queue.h"

Queue *init_queue(size_t capacity)
{
    return init_RB(capacity);
}

void deinit_queue(Queue *queue, void (*elem_dealloc_func)(void *))
{
    return deinit_RB(queue, elem_dealloc_func);
}

void print_queue(Queue *queue, void (*print_func)(void *))
{
    return print_buffer(queue, print_func);
}

void enqueue(Queue *queue, void *data)
{
    return enqueue_buff(queue, data);
}

void *dequeue(Queue *queue)
{
    return dequeue_buff(queue);
}
