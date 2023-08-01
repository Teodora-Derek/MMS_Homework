#include <stdio.h>
#include <inttypes.h>

typedef struct DoubleBitfield
{
    uint64_t mantissa : 52;
    uint16_t exponent : 11;
    int8_t sign : 1;
} DoubleBitfield;

typedef union MyDouble
{
    double d;
    DoubleBitfield rep;
} MyDouble;

int main(void)
{
    MyDouble myD;
    scanf("%lf", &(myD.d));
    printf("SIGN: %" PRId8 "\nEXPONENT: %" PRIu16 "\nMANTISSA: %" PRIx64 "\n", myD.rep.sign, myD.rep.exponent, myD.rep.mantissa);
    return 0;
}