#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define COUNT 10
/*Направете структура Book, която да има:
Заглавие - до 150 символа;
Автор - до 100 символа;
Брой страници;
Цена.

Да се направи масив от COUNT (предпроцесорна константа) книги. Да се генерират автоматично произволни данни,
с които да се запълни масива от книги.
Ограничения за произволните данни:
Заглавие и име на автора - между 10 и 20 символа, само малки и главни латински букви;
Брой страници - между 5 и 2000;
Цена - между - 1.00 и 1000.00.
Да се сортира масива по:
азбучен ред на заглавието - ASC/DESC;
азбучен ред на автора - ASC/DESC;
брой страници - ASC/DESC;
цена - ASC/DESC.
За сортирането да се използва функцията qsort()

Да се изведат сортираните данни в подходящ формат.
*/

typedef struct Book
{
    char titel[150];
    char author[100];
    uint16_t pages;
    double price;
} Book;

Book books[COUNT];

void fill_books();
char *gen_rand_str(size_t start, size_t stop, size_t *buffer_count);
int titel_ascending(const void *p1, const void *p2);
int titel_descending(const void *p1, const void *p2);
int author_ascending(const void *p1, const void *p2);
int author_descending(const void *p1, const void *p2);
int pages_ascending(const void *p1, const void *p2);
int pages_descending(const void *p1, const void *p2);
int price_ascending(const void *p1, const void *p2);
int price_descending(const void *p1, const void *p2);
void print_books();

int main(void)
{
    printf("The size of the book struct is: %llu\n", sizeof(Book));

    fill_books();
    qsort(books, COUNT, sizeof(*books), titel_ascending);
    print_books();

    printf("---------");
    return 0;
}

void fill_books()
{
    for (size_t i = 0; i < COUNT; i++)
    {
        size_t titel_source_count = 0;
        char *titel_source = gen_rand_str(10UL, 10UL, &titel_source_count);

        size_t author_source_count = 0;
        char *author_source = gen_rand_str(10UL, 10UL, &author_source_count);

        Book book;
        strncpy(book.titel, titel_source, titel_source_count);
        book.titel[titel_source_count] = '\0';

        strncpy(book.author, author_source, author_source_count);
        book.author[author_source_count] = '\0';

        book.price = (100 + rand() % 900000) / 100.;
        book.pages = 5 + rand() % 1995;

        books[i] = book;
        free(titel_source);
        free(author_source);
    }
}

char *gen_rand_str(size_t start, size_t stop, size_t *buffer_count)
{
    *buffer_count = start + rand() % stop;
    char *titel_buffer = malloc(*buffer_count * sizeof(*titel_buffer));
    for (size_t i = 0; i < *buffer_count; i++)
    {
        if (i % 2 == 0)
            titel_buffer[i] = 'A' + rand() % ('Z' - 'A');
        else
            titel_buffer[i] = 'a' + rand() % ('z' - 'a');
    }
    return titel_buffer;
}

int titel_ascending(const void *p1, const void *p2)
{
    return strcmp(((Book *)p1)->titel, ((Book *)p2)->titel);
}

int titel_descending(const void *p1, const void *p2)
{
    return -(strcmp(((Book *)p1)->titel, ((Book *)p2)->titel));
}
int author_ascending(const void *p1, const void *p2)
{
    return strcmp(((Book *)p1)->author, ((Book *)p2)->author);
}

int author_descending(const void *p1, const void *p2)
{
    return -(strcmp(((Book *)p1)->author, ((Book *)p2)->author));
}

int pages_ascending(const void *p1, const void *p2)
{
    return (int)((Book *)p1)->pages - ((Book *)p2)->pages;
}

int pages_descending(const void *p1, const void *p2)
{
    return (int)-(((Book *)p1)->pages - ((Book *)p2)->pages);
}

int price_ascending(const void *p1, const void *p2)
{
    return (int)(((Book *)p1)->price - ((Book *)p2)->price) * 100;
}

int price_descending(const void *p1, const void *p2)
{
    return (int)-((((Book *)p1)->price - ((Book *)p2)->price)) * 100;
}

void print_books()
{
    for (size_t i = 0; i < COUNT; i++)
        printf("Titel: %s \nAuthor:%s \nPages: %hu \nPrice: %lf \n\n",
               books[i].titel, books[i].author, books[i].pages, books[i].price);
    printf("\n");
}
