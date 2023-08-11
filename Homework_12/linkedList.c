#include <stdio.h>
#include <stdlib.h>

typedef struct Data
{
    int val;
} Data;

typedef struct Node
{
    Data val;
    Node *next;
} Node;

int count;
void printLinkedList(Node *head);
void pushBack(Data new_data, Node *head);
void popBack(Node *head, Data *result);

int main(void)
{
    scanf("%d", &count);
    Data data = {10};
    Node n1 = {data, NULL};
    Node *head = &data;
    return 0;
}

void printLinkedList(Node *head)
{
    Node *curr = head;
    while (curr != NULL)
    {
        printf("%d ", curr->val);
        curr = curr->next;
    }
    printf("\n");
}

void pushBack(Data new_data, Node *head)
{
    if (head == NULL)
    {
        printf("The head is NULL.");
        return;
    }
    head = initLinkedList(&new_data);
    Node *curr = head;
    while (curr->next != NULL)
        curr = curr->next;
    curr->next = malloc(sizeof(*(curr->next)));
    curr->val = new_data;
}

void popBack(Node *head, Data *result)
{
    if (head == NULL)
    {
        printf("The head is NULL.");
        return;
    }
    Node *curr = head;
    while (curr->next != NULL)
        curr = curr->next;
    Node *result = curr;
    curr->next = NULL;
}
