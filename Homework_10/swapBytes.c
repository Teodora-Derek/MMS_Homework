#include <stdio.h>
#include <stdint.h>

void swapBytes(uint16_t *word);

int main(void)
{
    uint16_t num = 0b0000111111111111;
    printf("0b%d\n", num);
    swapBytes(&num);
    printf("0b%d\n", num);
    return 0;
}

void swapBytes(uint16_t *word)
{
    *word = (*word << 8) | (*word >> 8);
    // 0000_1111 1111_1111
    //
    // (*word << 8) -> 1111_1111 0000_0000
    //  |
    // (*word >> 8) -> 0000_0000 0000_1111
    //                 1111_1111 0000_1111
}
