#include <stdio.h>
#include <stdarg.h>

/*Направете имплементация на функцията от стандартната библиотека printf:
int my_printf(const char *fmt, …);

Функцията приема символен низ, определящ формата чрез fmt.
Като минимум във fmt могат да се срещнат форматните спецификатори %d, %f, %c.
Колкото форматни спецификатори са предадени,толкова аргумента от
командия ред трябва да бъдат изпечатани с printf. Във fmt могат да се срещнат и символи,
които не са част от форматен спецификатор.

За печатане на символи на стандартния изход, използвайте putc.
Функцията връща броя на символите, които е изпечатала.

Направете примерни извиквания на my_printf.
*/

int my_printf(const char *fmt, ...);
int print_integer(int n);
int print_double(double n);

int main(void)
{
    int n = my_printf("Tedy %d top %f abc %c\n", 10, -3.14, 97);
    printf("Number of chars printed: %d\n", n);
    return 0;
}

int my_printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int printed_chars = 0;
    while (*fmt)
    {
        if (*fmt == '%')
        {
            fmt++;
            switch (*fmt)
            {
            case 'd':
                int num = va_arg(args, int);
                printed_chars += print_integer(num);
                break;
            case 'c':
                char ch = (char)va_arg(args, int);
                putc(ch, stdout);
                printed_chars++;
                break;
            case 'f':
                double d = va_arg(args, double);
                printed_chars += print_double(d);
                break;
            default:
                putc(*fmt, stdout);
                printed_chars++;
                break;
            }
        }
        else
        {
            putc(*fmt, stdout);
            printed_chars++;
        }
        fmt++;
    }
    va_end(args);
    return printed_chars;
}

int print_integer(int n)
{
    int printed_chars = 0;
    char buffer[20];
    int i = 0;
    if (n == 0)
    {
        putc('0', stdout);
        return 1;
    }
    else if (n < 0)
    {
        putc('-', stdout);
        printed_chars++;
        n = -n;
    }

    while (n > 0)
    {
        buffer[i++] = '0' + (n % 10);
        n /= 10;
    }
    while (i > 0)
    {
        putc(buffer[--i], stdout);
        printed_chars++;
    }
    return printed_chars;
}

int print_double(double n)
{
    int printed_chars = 0;
    if (n < 0)
    {
        putc('-', stdout);
        printed_chars++;
        n = -n;
    }

    int integer_part = (int)n;
    printed_chars += print_integer(integer_part);

    putc('.', stdout);
    printed_chars++;

    double fractional_part = n - integer_part;
    int float_mantissa_presision = 6;
    for (int i = 0; i < float_mantissa_presision; i++)
    {
        fractional_part *= 10;
        int digit = (int)fractional_part;
        putc('0' + digit, stdout);
        printed_chars++;
        fractional_part -= digit;
    }
    return printed_chars;
}
