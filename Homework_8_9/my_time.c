#include <stdio.h>
#include <stdint.h>
#include <time.h>

/*Създайте структурата MyTime, която пази информация за :
година
месец
ден
час
минути
секунди

Изполвайте подходящи типове и член данни, така че размерът на структурата да е възможно най-малък.
Изпечатайте размера на структурата в main.

Реализирайте следните функции:
int isLeapYear(MyTime t) - връща 1 ако годината е високосна и 0 ако годината не е високосна
int totalDaysInYear(MyTime t) - връща броя на дните в годината
void printMonth(MyTime t) - печата символен низ, отговарящ на месеца
int secondsPassed(MyTime t) - печата общия брой изминали секунди от 1 януари 1970 година.

Направете примерни извиквания в main.
*/

typedef struct MyTime
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minutes;
    uint8_t seconds;
} MyTime;

int isLeapYear(MyTime t);
int totalDaysInYear(MyTime t);
void printMonth(MyTime t);
int secondsPassed(MyTime t);

int main(void)
{
    printf("The size of MyTime is: %llu\n", sizeof(MyTime));

    MyTime time = {2023, 8, 2, 12, 34, 56};

    printf("Is leap year: %d\n", isLeapYear(time));

    printf("Total days in year: %d\n", totalDaysInYear(time));

    printMonth(time);

    printf("Total seconds passed since January 1, 1970: %d\n", secondsPassed(time));

    return 0;
}

int isLeapYear(MyTime t)
{
    return t.year % 4 == 0 ? 1 : 0;
}

int totalDaysInYear(MyTime t)
{
    return isLeapYear(t) ? 366 : 365;
}

void printMonth(MyTime t)
{
    if (t.month <= 0 || t.month > 12)
    {
        printf("The month you entered is invaalid.\n");
        return;
    }

    char buffer[3];
    sprintf(buffer, "%d", t.month);
    printf("Month: %s\n", buffer);
}

int secondsPassed(MyTime t)
{
    time_t time;
    struct tm timeInfo;
    timeInfo.tm_year = t.year - 1900;
    timeInfo.tm_mon = t.month - 1;
    timeInfo.tm_mday = t.day;
    timeInfo.tm_hour = t.hour;
    timeInfo.tm_min = t.minutes;
    timeInfo.tm_sec = t.seconds;
    timeInfo.tm_isdst = -1;

    time = mktime(&timeInfo);
    return (int)time;
}
