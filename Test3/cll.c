#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct CLL
{
    Node *head;
    Node *tail;
} CLL;

CLL *init_cll(int elem_number);
void deinit_cll(CLL *list, int elem_number);
void print(struct Node *cll);
struct Node *insertAfter(struct Node *cll, int skipCount, int newElem);

int main(void)
{
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    if (n <= 0)
    {
        printf("Invalid number of elements.\n");
        return 1;
    }

    CLL *list = init_cll(n);
    list->head = NULL;
    list->tail = NULL;

    int elem;
    printf("Enter element: ");
    scanf("%d", &elem);

    list->head = malloc(sizeof(Node));
    list->head->data = elem;
    list->tail = list->head;

    Node *curr = list->head->next;
    for (int i = 1; i < n - 1; i++)
    {
        printf("Enter element: ");
        scanf("%d", &elem);
        curr = malloc(sizeof(Node));
        curr->data = elem;
        curr = curr->next;
    }
    curr = malloc(sizeof(Node));
    list->tail = curr;
    list->tail->next = list->head;

    print(list->head);
    deinit_cll(list, n);
    free(list);
    return 0;
}

CLL *init_cll(int elem_number)
{
    return malloc(sizeof(Node) * elem_number);
}

void deinit_cll(CLL *list, int elem_number)
{
    Node *head = list->head;
    for (int i = 0; i < elem_number; i++)
    {
        head = head->next;
        free(head);
    }
    free(head);
}

void print(Node *cll)
{
    if (!cll)
    {
        printf("Node is null\n");
        return;
    }

    while (cll)
    {
        printf("%d ", cll->data);
        cll = cll->next;
    }
}

Node *insertAfter(Node *cll, int skipCount, int newElem)
{
    Node *curr = cll;
    for (int i = 0; i < skipCount; i++)
        curr = curr->next;

    Node *prev = curr;
    curr = malloc(sizeof(Node));
    curr->data = newElem;
    curr->next = prev;

    return curr;
}
