#include "double_linked_list.h"
#include "ringbuffer.h"
#include "stack.h"
#include "queue.h"

typedef struct Data
{
    int num;
} Data;

void print_data(void *data);
void print_double(void *d);
void rb_elem_deinit_func(void *);

int main(void)
{
    size_t capacity = 5;
    Queue *queue = init_queue(capacity);
    Data d1 = {.num = 1};
    Data d2 = {.num = 2};
    Data d3 = {.num = 3};

    enqueue(queue, &d1);
    print_queue(queue, &print_data);
    enqueue(queue, &d2);
    print_queue(queue, &print_data);
    enqueue(queue, &d3);
    print_queue(queue, &print_data);

    Data *result;
    result = dequeue(queue);
    printf("The returned data is: %d\n", result->num);
    print_queue(queue, &print_data);

    result = dequeue(queue);
    printf("The returned data is: %d\n", result->num);
    print_queue(queue, &print_data);

    result = dequeue(queue);
    printf("The returned data is: %d\n", result->num);
    print_queue(queue, &print_data);

    deinit_queue(queue, rb_elem_deinit_func);

    // Stack *stack = init_linked_list();
    // Data d1 = {.num = 1};
    // Data d2 = {.num = 2};

    // push(stack, &d1);
    // print_linked_list(stack, &print_data);
    // push(stack, &d2);
    // print_linked_list(stack, &print_data);

    // Data *result;
    // result = pop(stack);
    // printf("The returned data is: %d\n", result->num);
    // print_linked_list(stack, &print_data);

    // result = pop(stack);
    // printf("The returned data is: %d\n", result->num);
    // print_linked_list(stack, &print_data);

    // deinit_stack(stack);

    // size_t capacity = 5;
    // RingBuffer *rb = init_RB(capacity);

    // double a = 3.5;
    // enqueue(rb, &a);

    // double *result = (double *)dequeue(rb);
    // print_double(result);

    // print_buffer(rb, print_double);
    // deinit_RB(rb, rb_elem_deinit_func);

    // LinkedList *ll = init_linked_list();
    // Data data1 = {.num = 1};
    // Data data2 = {.num = 2};
    // Data data3 = {.num = 3};
    // Data data4 = {.num = 4};

    // push_front(ll, &data1);
    // print_linked_list(ll, &print_data);
    // push_back(ll, &data2);
    // print_linked_list(ll, &print_data);
    // push_front(ll, &data3);
    // print_linked_list(ll, &print_data);
    // push_back(ll, &data4);
    // print_linked_list(ll, &print_data);

    // Data *result;
    // result = pop_back(ll);
    // printf("The returned data is: %d\n", result->num);
    // print_linked_list(ll, &print_data);

    // result = pop_front(ll);
    // printf("The returned data is: %d\n", result->num);
    // print_linked_list(ll, &print_data);

    // result = pop_back(ll);
    // printf("The returned data is: %d\n", result->num);
    // print_linked_list(ll, &print_data);

    // result = pop_front(ll);
    // printf("The returned data is: %d\n", result->num);
    // print_linked_list(ll, &print_data);

    // deinit_linked_list(ll);
    return 0;
}

void print_data(void *data)
{
    printf("%d    ", ((Data *)data)->num);
}

void print_double(void *d)
{
    printf("%f ", *((double *)d));
}

void rb_elem_deinit_func(void *)
{
    return;
}