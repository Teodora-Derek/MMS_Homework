#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "double_linked_list.h"
#define COUNT 10

typedef struct Book
{
    char titel[150];
    char author[100];
    uint16_t pages;
    double price;
} Book;

char get_random_char();
char *gen_rand_string();
void gen_rand_book(Book *book);
void print_book(void *book);
int titel_ascd_cmp(const void *b1, const void *b2);
int titel_desc_cmp(const void *b1, const void *b2);

int main(void)
{
    LinkedList *ll = init_linked_list();

    for (int i = 0; i < COUNT; i++)
    {
        Book *book = malloc(sizeof(*book));
        gen_rand_book(book);
        push_back(ll, (void *)book);
    }

    printf("-----Unsorted:-----\n");
    print_linked_list(ll, &print_book);

    printf("------Sorted in ascending order by titel:------\n");
    sort_linked_list(ll, titel_ascd_cmp);
    print_linked_list(ll, &print_book);

    printf("------Sorted in descending order by titel:------\n");
    sort_linked_list(ll, titel_desc_cmp);
    print_linked_list(ll, &print_book);

    deinit_linked_list(ll);
    return 0;
}

char *gen_rand_string()
{
    size_t len = 10 + rand() % 10;
    char *temp = malloc(len + 1);

    for (size_t i = 0; i < len; i++)
        temp[i] = get_random_char();

    temp[len] = '\0';
    return temp;
}

void gen_rand_book(Book *book)
{
    char *titel = gen_rand_string();
    strcpy(book->titel, titel);
    free(titel);

    char *author = gen_rand_string();
    strcpy(book->author, author);
    free(author);

    book->pages = 5 + rand() % 1996;
    book->price = (100 + rand() % 100000) / 100;
}

void print_book(void *book)
{
    printf("Titel: %s\n", ((Book *)book)->titel);
    printf("Author: %s\n", ((Book *)book)->author);
    printf("Pages: %hu\n", ((Book *)book)->pages);
    printf("Price: %.2f\n", ((Book *)book)->price);
    printf("\n");
}

int titel_ascd_cmp(const void *b1, const void *b2)
{
    return strcmp(((Book *)b1)->titel, ((Book *)b2)->titel);
}

int titel_desc_cmp(const void *b1, const void *b2)
{
    return strcmp(((Book *)b2)->titel, ((Book *)b1)->titel);
}

char get_random_char()
{
    int lowercase = rand() % 2;
    char base_char = lowercase ? 'a' : 'A';
    return base_char + rand() % 26;
}
