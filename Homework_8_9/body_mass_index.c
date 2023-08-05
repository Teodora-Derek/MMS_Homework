#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

typedef int (*comparator)(void *, void *, size_t);

typedef struct Point
{
    double x;
    double y;
    double z;
} Point;

typedef struct Human
{
    float weight_kg;
    float height_meter;
} Human;

int findMax(void *target, void *array, int comparator_idx, size_t n);
int max_elem_comp(uint64_t *target, uint64_t *array, size_t n);
int max_distance_comp(Point *target, Point *array, size_t n);
int least_bmi_comp(Human *target, Human *array, size_t n);
int max_set_bits_comp(float *target, float *array, size_t n);
int count_ones(int num);

int main(void)
{
    uint64_t arr[] = {1, 2654, 2, 9, 456, 78624};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    uint64_t target;
    findMax((void *)(&target), (void *)arr, 1, n);

    Human h[] = {(Human){.weight_kg = 60, .height_meter = 1.70},
                 (Human){.weight_kg = 50, .height_meter = 1.80},
                 (Human){.weight_kg = 80, .height_meter = 1.90}};
    n = sizeof(h) / sizeof(h[0]);
    Human human;
    findMax((void *)(&human), (void *)h, 3, n);

    return 0;
}

/* 1. За да намерите най-големия елемент в масив от тип uint64_t.

2. За да намерите точката, която е на най-голямо (евклидово)
разстояние от (0, 0, 0) в масив от тип Point.

3. За да намерите човека с най-нисък Body Mass Index в масив от тип Human.
Body Mass Index = weight_kg / (height_meter*height_meter)

4.За да намерите числото с най-много битове в двоичното представяне,
които са 1, в масив от тип float.*/

int findMax(void *target, void *array, int comparator_idx, size_t n)
{
    int res = -1;
    switch (comparator_idx)
    {
    case 1:
        res = max_elem_comp((uint64_t *)target, (uint64_t *)array, n);
        printf("max_elem_comp -> target: %lld\n", *((uint64_t *)target));
        break;

    case 2:
        res = max_distance_comp((Point *)target, (Point *)array, n);
        printf("max_distance_comp -> target (x, y, z): %f %f %f\n", ((Point *)target)->x, ((Point *)target)->y, ((Point *)target)->z);
        break;

    case 3:
        res = least_bmi_comp((Human *)target, (Human *)array, n);
        printf("least_bmi_comp -> target weight: %f\n", ((Human *)target)->weight_kg);
        break;

    case 4:
        res = max_set_bits_comp((float *)target, (float *)array, n);
        printf("max_set_bits_comp -> target: %f\n", *((float *)target));
        break;
    default:
        printf("Unimplemented comparer.\n");
        exit(EXIT_FAILURE);
        break;
    }
    return res;
}

int max_elem_comp(uint64_t *target, uint64_t *array, size_t n)
{
    if (!array || !target)
        return 1;

    (*target) = array[0];
    for (size_t i = 1; i < n; i++)
    {
        if (*target < array[i])
        {
            (*target) = (*target) ^ array[i];
            array[i] = (*target) ^ array[i];
            (*target) = (*target) ^ array[i];
        }
    }

    return 0;
}

int max_distance_comp(Point *target, Point *array, size_t n)
{
    if (!array || !target)
        return 1;

    (*target) = array[0];
    Point curr;
    for (size_t i = 1; i < n; i++)
    {
        curr = array[i];
        if (sqrtf((target->x * target->x) + (target->y * target->y) + (target->z * target->z)) <
            sqrtf((curr.x * curr.x) + (curr.y * curr.y) + (curr.z * curr.z)))
        {
            *target = curr;
        }
    }

    return 0;
}

int least_bmi_comp(Human *target, Human *array, size_t n)
{
    if (!array || !target)
        return 1;

    (*target) = array[0];
    Human curr;
    for (size_t i = 1; i < n; i++)
    {
        curr = array[i];
        if (target->weight_kg / (target->height_meter * target->height_meter) >
            curr.weight_kg / (curr.height_meter * curr.height_meter))
        {
            *target = curr;
        }
    }
    return 0;
}

int max_set_bits_comp(float *target, float *array, size_t n)
{
    if (!array || !target)
        return 1;

    int max_ones = 0;
    *target = array[0];

    for (size_t i = 0; i < n; i++)
    {
        int num_as_int = *((int *)&array[i]);
        int ones_count = count_ones(num_as_int);

        if (ones_count > max_ones)
        {
            max_ones = ones_count;
            *target = array[i];
        }
    }
    return 0;
}

int count_ones(int num)
{
    int count = 0;
    while (num != 0)
    {
        count += num & 1;
        num >>= 1;
    }
    return count;
}
