#include "double_linked_list.h"
#include "deque.h"

int main(void)
{
    // LinkedList *ll = init_linked_list();
    // push_back(ll, (Data){1});
    // print_linked_list(*ll);
    // push_back(ll, (Data){2});
    // print_linked_list(*ll);
    // push_back(ll, (Data){3});
    // print_linked_list(*ll);
    // push_back(ll, (Data){4});
    // print_linked_list(*ll);

    // Data d;
    // pop_back(ll, &d);
    // print_linked_list(*ll);
    // pop_front(ll, NULL);
    // print_linked_list(*ll);
    // pop_front(ll, NULL);
    // print_linked_list(*ll);
    // deinit_linked_list(ll);

    Deque *deque = init_deque();
    insertRear(deque, (Data){1});
    print_deque(*deque);
    insertRear(deque, (Data){2});
    print_deque(*deque);
    insertRear(deque, (Data){3});
    print_deque(*deque);
    insertRear(deque, (Data){4});
    print_deque(*deque);

    Data d;
    deleteRear(deque, &d);
    print_deque(*deque);
    deleteFront(deque, &d);
    print_deque(*deque);
    deleteFront(deque, &d);
    print_deque(*deque);
    deinit_deque(deque);

    return 0;
}