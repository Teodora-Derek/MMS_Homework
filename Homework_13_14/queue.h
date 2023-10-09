#include "ringbuffer.h"

#ifndef QUEUE_H
#define QUEUE_H 2

typedef struct RingBuffer Queue;

Queue *init_queue(size_t capacity);
void deinit_queue(Queue *queue, void (*elem_dealloc_func)(void *));
void print_queue(Queue *queue, void (*print_func)(void *));
void enqueue(Queue *queue, void *data);
void *dequeue(Queue *queue);

#endif
