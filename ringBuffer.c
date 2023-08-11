#include <stdio.h>
#define N 10

double arr[N];
size_t start_index = 0, end_index = 0, count = 0;

void printBuffer();

int main(void)
{
    return 0;
}

void print_buffer()
{
    for (size_t i = 0; i < N; i++)
    {
        if (arr[i] != 0)
            printf("%3.2lf ", arr[i]);
        else
            printf(" --- ");
    }
    printf("\n");
}

void enqueue(double d)
{
    if (count != 0)
    {
        if (start_index < end_index)
        {
            arr[end_index % N] = d;
            end_index++;
        }
        else
        {
            printf("The buffer is full.\n");
            return;
        }
    }
    else
    {
        arr[end_index % N] = d;
        end_index++;
    }
    count++;
}

double dequeue()
{
    size_t old_start = start_index;
    arr[old_start] = 0;
    start_index++;
    return arr[old_start % N];
}