#include "ringbuffer.h"

RingBuffer *init_RB(size_t capacity)
{
    RingBuffer *rb = malloc(sizeof(*rb));

    if (!rb)
        exit(-1);

    rb->buffer_capacity = capacity;
    rb->start_index = 0;
    rb->end_index = 0;
    rb->arr = (void **)calloc(capacity, sizeof(void *));

    return rb;
}

void deinit_RB(RingBuffer *rb, void (*elem_dealloc_func)(void *))
{
    for (size_t i = 0; i < rb->buffer_capacity; i++)
        if (rb->arr[i])
            elem_dealloc_func(rb->arr[i]);

    free(rb->arr);
    free(rb);
}

void print_buffer(RingBuffer *rb, void (*print_func)(void *))
{
    for (size_t i = 0; i < rb->buffer_capacity; i++)
    {
        if (rb->arr[i] != NULL)
            print_func((char *)rb->arr[i]);
        else
            printf("---- ");
    }
    printf("\n");
}

void enqueue_buff(RingBuffer *rb, void *data)
{
    if (rb->start_index > rb->buffer_capacity)
    {
        rb->start_index -= rb->buffer_capacity;
        rb->end_index -= rb->buffer_capacity;
    }
    else if (rb->end_index - rb->start_index == rb->buffer_capacity)
    {
        perror("Ring buffer is full.");
        return;
    }

    rb->arr[rb->end_index % rb->buffer_capacity] = (char *)data;
    rb->end_index++;
}

void *dequeue_buff(RingBuffer *rb)
{
    if (rb->end_index - rb->start_index == 0)
    {
        perror("Ring buffer is empty");
        return NULL;
    }

    char *dequeued_elem = (char *)rb->arr[rb->start_index];
    rb->arr[rb->start_index] = NULL;
    rb->start_index++;

    return (void *)dequeued_elem;
}
