#include "double_linked_list.h"

typedef struct Data
{
    int num;
} Data;

void print_data(void *data);

int main(void)
{
    LinkedList *ll = init_linked_list();
    Data data1 = {.num = 1};
    Data data2 = {.num = 2};
    Data data3 = {.num = 3};
    Data data4 = {.num = 4};

    push_front(ll, &data1);
    print_linked_list(ll, &print_data);
    push_back(ll, &data2);
    print_linked_list(ll, &print_data);
    push_front(ll, &data3);
    print_linked_list(ll, &print_data);
    push_back(ll, &data4);
    print_linked_list(ll, &print_data);

    Data *result;
    result = pop_back(ll);
    printf("The returned data is: %d\n", result->num);
    print_linked_list(ll, &print_data);

    result = pop_front(ll);
    printf("The returned data is: %d\n", result->num);
    print_linked_list(ll, &print_data);

    result = pop_back(ll);
    printf("The returned data is: %d\n", result->num);
    print_linked_list(ll, &print_data);

    result = pop_front(ll);
    printf("The returned data is: %d\n", result->num);
    print_linked_list(ll, &print_data);

    deinit_linked_list(ll);
    return 0;
}

void print_data(void *data)
{
    printf("%d ", ((Data *)data)->num);
}