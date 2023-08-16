/*Задача 3:
1.1 Направете макрос MAX(x, y, z) , който връща най-голямото от три числа.
1.2 Направете макрос MIN(x, y, z) , който връща най-малкото от три числа.
1.3 Направете побитов макрос SETBIT(mask, bit) , който установява определен бит в 1 в побитовата маска.
1.4 Направете побитов макрос CLEARBIT(mask, bit) , който установява определен бит в 0 в побитовата маска.
1.5 Направете побитов макрос INVERSEBIT(mask, bit) , който обръща определен в побитовата маска.
1.6 Направете побитов макрос CHECKBIT(mask, bit), който връща 0 или 1 в зависимост от състоянието на бита.
1.7 Направете побитов макрос SWAP(a, b) , който разменя две променливи.
*/
#include <stdio.h>
#define MAX(x, y, z)                       \
    (x > y ? (x > z) ? x : z : (y > z) ? y \
                                       : z)
#define MIN(x, y, z)                       \
    (x < y ? (x < z) ? x : z : (y < z) ? y \
                                       : z)
#define SETBIT(mask, i) \
    ((mask) |= (i << 1ULL))

#define CLEARBIT(mask, i) \
    ((mask) &= ~(i << 1ULL))

#define INVERSEBIT(mask, i) \
    ((mask) ^= (i << 1ULL))

#define CHECKBIT(mask, i) \
    ((mask & (i << 1ULL)) ? 1 : 0)

#define SWAP(a, b)  \
    if (1)          \
    {               \
        (a) ^= (b); \
        (b) ^= (a); \
        (a) ^= (b); \
    }

int main(void)
{
    int x = 5, y = 10, z = 3;
    printf("Maximum of %d, %d, %d is %d\n", x, y, z, MAX(x, y, z));
    printf("Minimum of %d, %d, %d is %d\n", x, y, z, MIN(x, y, z));

    unsigned int mask = 0b1010;
    SETBIT(mask, 2);
    printf("After setting bit 2: %x\n", mask);

    CLEARBIT(mask, 1);
    printf("After clearing bit 1: %x\n", mask);

    INVERSEBIT(mask, 0);
    printf("After inverting bit 0: %x\n", mask);

    printf("Bit 2 in mask is %d\n", CHECKBIT(mask, 2));

    int a = 5, b = 10;
    SWAP(a, b);
    printf("After swapping: a = %d, b = %d\n", a, b);

    return 0;
}