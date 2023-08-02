#include <stdio.h>
#include <stdlib.h>

int *initArr(size_t n);
void fillArr(int *arr, size_t *count, int start, int end);
void reallocArr(int *arr, size_t *count, size_t newCount, int start, int end);
void printArr(int *arr, size_t count);

int main(void)
{
    size_t n, m, p;
    scanf("%ld", &n);
    int *arr = initArr(n);
    fillArr(arr, &n, 0, 100);
    scanf("%ld", &m);
    reallocArr(arr, &n, m, 100, 100);
    scanf("%ld", &p);
    reallocArr(arr, &n, m, 200, 100);
    printArr(arr, n);
    free(arr);
    return 0;
}

/*Направете програма, в която потребителят въвежда от стандартния вход цяло число n.
След това да се създаде масив от реални числа от n на брой елементи в динамичната памет.
Елементите на масива да се инициализират с произволни стойности между 0,0 и 1.0.
След това се въвежда ново число m и масивът се да се разшири с нови m елемента.
Новите елементи да се инициализират с числа между 1.0 и 2.0. След това да се въведе цяло число p.
Масивът да се разшири с нови p елемента. Новите елементи да се инициализират с числа между 2.0 и 3.0.
Накрая да се изведе масива в стандартния изход. Да се освободи заетата памет.
Да се следи дали всяка функция успешно заделя памет.
*/

int *initArr(size_t n)
{
    return malloc(n * sizeof(double));
}

void fillArr(int *arr, size_t *count, int start, int end)
{
    for (size_t i = 0; i < *count; i++)
        arr[i] = (start + rand() % end) / 100.;
}

void reallocArr(int *arr, size_t *count, size_t newCount, int start, int end)
{
    *count = (*count + newCount) * sizeof(double);
    arr = realloc(arr, *count);
    fillArr(arr, count, start, end);
}

void printArr(int *arr, size_t count)
{
    for (size_t i = 0; i < count; i++)
        printf("%d ", arr[i]);
    printf("---------");
}
