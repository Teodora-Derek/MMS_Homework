#include <stdio.h>
#include <math.h>

void filter_and_map(
    const int arr[],
    size_t n,
    int (*filter_f)(int),
    int (*map_f)(int),
    int dest[],
    size_t *dest_cnt);
int isPositive(int a);
int addOne(int a);
int squarePrime(int n);
int checkBit(int n);

int printEven(int a);
int isEven(int a);
int isPrime(int n);

int main(void)
{
    int arr[8] = {1, 2, 3, 4, -1, -2, 11, -100};
    int dest[10];
    size_t new_size = 0;
    filter_and_map(arr, 8, isPositive, addOne, dest, &new_size);
    filter_and_map(arr, 8, isEven, printEven, dest, &new_size);
    filter_and_map(arr, 8, isPrime, squarePrime, dest, &new_size);
    filter_and_map(arr, 8, isPositive, checkBit, dest, &new_size);
    printf("new_size: %u\n", new_size);
    for (size_t i = 0; i < new_size; i++)
        printf("dest[%llu]: %d\n", i, dest[i]);

    return 0;
}

void filter_and_map(const int arr[], size_t n, int (*filter_f)(int), int (*map_f)(int), int dest[], size_t *dest_cnt)
{
    if (dest == NULL)
        return;
    int filter_f_result = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (!filter_f(arr[i]))
            continue;
        else // za true value-tata na filter_f(i) ->
        {
            *(dest + *dest_cnt) = map_f(arr[i]);
            (*dest_cnt)++;
        }
    }
}

int isPositive(int a)
{
    return a > 0 ? 1 : 0;
}

int addOne(int a)
{
    return ++a;
}

int squarePrime(int n)
{
    return n * n;
}

int checkBit(int n)
{
    int sum = 0;
    for (size_t i = 0; i < 32; i++)
        sum += !!(n & (1 << i));
    return sum;
}

int printEven(int a)
{
    printf("%d ", a);
    return a;
}

int isEven(int a)
{
    return a % 2 == 0 ? 1 : 0;
}

int isPrime(int n)
{
    int flag = 1;

    // change flag to 0 for non-prime number
    if (n <= 1)
        flag = 0;

    for (int i = 2; i <= sqrt(n); ++i)
        if (n % i == 0)
        {
            flag = 0;
            break;
        }

    // flag is 1 for prime numbers
    return flag;
}
