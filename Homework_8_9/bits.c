#include <stdio.h>
#include <stdint.h>

/*Направете функции, които обработват масив от 32 битови маски - maskArr.
nitems показва броя на елементите в масива, а bit, показва номера на бита, който да се обработи.
При успех - функциите връщат 0. Ако има проблем, функциите връщат -1.

int clearBits(uint32_t* maskArr, size_t nitems, size_t bit_index);
За всички елементи на масива maskArr се задава стойността на бита с индекс bit_index да бъде 0.

int setBits(uint32_t* maskArr, size_t nitems, size_t bit_index);
За всички елементи на масива maskArr се задава стойността на бита с индекс bit_index да бъде 1.

int checkBits(uint32_t* maskArr, size_t len, size_t bit_index);
Връща 0 ако всички елементи на maskArr имат стойност 0 на бита с индекс bit_index
Връща 1 ако всички елементи на maskArr имат стойност 1 на бита с индекс bit_index
Ако бита с индекс bit_index има стойност 1 за някои елементи на maskArr и
стойност 0 за други елементи на maskArr - това се счита за неуспех и функцията връща -1.
*/

int clearBits(uint32_t *maskArr, size_t nitems, size_t bit_index);
int setBits(uint32_t *maskArr, size_t nitems, size_t bit_index);
int checkBits(uint32_t *maskArr, size_t len, size_t bit_index);

int main(void)
{
    uint32_t maskArr[5] = {
        0b00000000000000000000000000000010,
        0b00000000000000100000000000000010,
        0b00000000000001000000000000000010,
        0b00000000000010000000000000000010,
        0b00000000000100000000000000000010,
    };
    int result = checkBits(maskArr, 5, 0);
    printf("%d", result);
    return 0;
}

int clearBits(uint32_t *maskArr, size_t nitems, size_t bit_index)
{
    if (maskArr == NULL)
        return 1;

    for (size_t i = 0; i < nitems; i++)
        maskArr[i] &= (~(1 << bit_index));

    return 0;
}

int setBits(uint32_t *maskArr, size_t nitems, size_t bit_index)
{
    if (maskArr == NULL)
        return 1;

    for (size_t i = 0; i < nitems; i++)
        maskArr[i] |= (1 << bit_index);

    return 0;
}

int checkBits(uint32_t *maskArr, size_t len, size_t bit_index)
{
    if (maskArr == NULL)
        return -1;

    uint32_t first_elem = *maskArr;
    int first_elem_bit = !!(first_elem & (1 << bit_index));

    if (len == 1)
        return first_elem_bit;

    for (size_t i = 1; i < len; i++)
        if (first_elem_bit != !!(maskArr[i] & (1 << bit_index)))
            return -1;

    return first_elem_bit ? 1 : 0;
}
