#include <stdio.h>
#include <stdint.h>

#define TINT 1
#define TCHAR 2
#define TDOUBLE 3
#define TFLOAT 4
#define TUINT8_T 5
#define TUINT16_T 6
#define TUINT32_T 7
#define TUINT64_T 8

void printValue(const void *valuePtr, uint8_t flag);

int main(void)
{
    int i = 1; 
    char c = 'A'; 
    double d = 2.3; 
    float f = 5.6; 
    uint8_t ui_8 = 235; 
    uint16_t ui_16 = 1234; 
    uint32_t ui_32 = 45623; 
    uint64_t ui_64 = 159357879;
    
    printValue(&i, 1);
    printValue(&c, 2);
    printValue(&d, 3);
    printValue(&f, 4);
    printValue(&ui_8, 5);
    printValue(&ui_16, 6);
    printValue(&ui_32, 7);
    printValue(&ui_64, 8);
    return 0;
}

void printValue(const void *valuePtr, uint8_t flag)
{
    switch (flag)
    {
        case TINT: printf("%d\n", *(const int *)valuePtr); break;
        case TCHAR: printf("%c\n", *(const char *)valuePtr); break;
        case TDOUBLE: printf("%lf\n", *(const double *)valuePtr); break;
        case TFLOAT: printf("%f\n", *(const float *)valuePtr); break;
        case TUINT8_T: printf("%u\n", *(const uint8_t *)valuePtr); break;
        case TUINT16_T: printf("%u\n", *(const uint16_t *)valuePtr); break;
        case TUINT32_T: printf("%u\n", *(const uint32_t *)valuePtr); break;
        case TUINT64_T: printf("%llu\n", *(const uint64_t *)valuePtr); break;
        default: printf("This is an unknown data poiner.\n"); break;
    }
}
