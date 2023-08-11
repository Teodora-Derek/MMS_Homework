#include <stdio.h>
#include <stdlib.h>

double *initArr(size_t n);
void fillArr(double *arr, size_t *count, int start, int end);
void reallocArr(double *arr, size_t *count, size_t newCount, int start, int end);
void printArr(double *arr, size_t count);

/*Направете програма, в която потребителят въвежда от стандартния вход цяло число n.
След това да се създаде масив от реални числа от n на брой елементи в динамичната памет.
Елементите на масива да се инициализират с произволни стойности между 0,0 и 1.0.
След това се въвежда ново число m и масивът се да се разшири с нови m елемента.
Новите елементи да се инициализират с числа между 1.0 и 2.0. След това да се въведе цяло число p.
Масивът да се разшири с нови p елемента. Новите елементи да се инициализират с числа между 2.0 и 3.0.
Накрая да се изведе масива в стандартния изход. Да се освободи заетата памет.
Да се следи дали всяка функция успешно заделя памет.
*/

int main(void)
{
    size_t n, m, p;
    printf("Enter n: ");
    scanf("%lld", &n);
    double *arr = initArr(n);
    fillArr(arr, &n, 0, 100);
    printArr(arr, n);

    printf("Enter m: ");
    scanf("%lld", &m);
    reallocArr(arr, &n, m, 100, 100);
    printArr(arr, n);

    printf("Enter p: ");
    scanf("%lld", &p);
    reallocArr(arr, &n, m, 200, 100);
    printArr(arr, n);
    free(arr);
    return 0;
}

double *initArr(size_t n)
{
    return malloc(n * sizeof(double));
}

void fillArr(double *arr, size_t *count, int start, int end)
{
    for (size_t i = 0; i < *count; i++)
        arr[i] = (start + rand() % end) / 100.;
}

void reallocArr(double *arr, size_t *count, size_t newCount, int start, int end)
{
    *count = (*count) + newCount;
    arr = realloc(arr, *count);
    fillArr(arr, count, start, end);
}

void printArr(double *arr, size_t count)
{
    for (size_t i = 0; i < count; i++)
        printf("%f ", arr[i]);
    printf("\n---------\n");
}
