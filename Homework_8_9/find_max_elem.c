#include <stdio.h>

/*Създайте функция, която намира максималния елемент в масив:
void* findMax(void* arr, size_t n, size_t elem_s, int (*cmp)(const void*, const void*));

Функцията трябва да може да намира максималния елемент в масиви от всякакъв тип:
void* arr - адресът на първия елемент в масива
size_t n - броя на елементите в масива
size_t elem_s - размерът на един елемент в байтове
int (*cmp)(const void*, const void*) - указател към функция, която приема адресите на 2 елемента от масива arr. Функцията сравнява елементите и:
връща 0 ако са еднакви
връща -1 ако първия аргумент е “по-голям”
връща 1 ако втория аргумент е “по-голям”

Като резултат функцията връща адреса на елемента, който е “най-голям”. Наредбата на елементите е определена от сравняващата функция cmp.

Функцията трябва да може да намира максималния елемент на масиви от всякакви типове.
*/

void *findMax(void *arr, size_t n, size_t elem_s, int (*cmp)(void *, void *));
int cmpInt(void *a, void *b);

int main(void)
{
    int arr[] = {1, 2, -1, 3, 5, 11, 12, 13, 2, 100, 22};
    int *max = findMax(arr, sizeof(arr) / sizeof(*arr), sizeof(*arr), cmpInt);
    printf("%d", *max); // should print 100
    return 0;
}

void *findMax(void *arr, size_t n, size_t elem_s, int (*cmp)(void *, void *))
{
    void *target;

    for (size_t step = 0; step < n - 1; ++step)
    {
        for (size_t i = 0; i < n - step - 1; ++i)
        {
            target = (char *)arr + i * elem_s;
            void *curr = (char *)arr + (i + 1) * elem_s;

            if (cmp(target, curr) > 0)
            {
                for (size_t j = 0; j < elem_s; ++j)
                {
                    *((char *)target + j) ^= *((char *)curr + j);
                    *((char *)curr + j) ^= *((char *)target + j);
                    *((char *)target + j) ^= *((char *)curr + j);
                }
            }
        }
    }
    return target;
}

int cmpInt(void *a, void *b)
{
    return *(int *)a > *(int *)b ? -1 : 1;
}