#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>

int printf_time(const char *format, ...);

int main(void)
{
    printf_time("%d %d ", 10, 20);
    return 0;
}

int printf_time(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    time_t t = time(NULL);
    struct tm *tm = gmtime(&t);
    char *str = asctime(tm);

    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';

    printf("[%s]: ", str);
    vprintf(format, args);
    va_end(args);
    return 0;
}
