#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define ID_LEN 11
#define PERSONARR_LEN 10

void *initArray(size_t capacity);
int addPerson(char *name, unsigned short birthYear, char *birthMonth, char *birthDay, char gender);
int removePerson(char *id);
void readPerson();
int printPerson(char *id);
void printArr();

typedef struct Person
{
    char name[100];
    char id[ID_LEN];
    unsigned short birthYear;
    char birthMonth[3];
    char birthDay[3];
    char gender;
} Person;

Person *personArr = NULL;
size_t index = 0;

int main(void)
{
    printf("%lld\n", sizeof(bool));
    printf("%lld\n", sizeof(Person));

    personArr = initArray(PERSONARR_LEN);
    readPerson();
    printArr();
    free(personArr);
    return 0;
}

void *initArray(size_t capacity)
{
    Person *personArr = malloc(sizeof(*personArr) * capacity);
    return personArr;
}

int addPerson(char *name, unsigned short birthYear, char *birthMonth, char *birthDay, char gender)
{
    if (index >= PERSONARR_LEN)
    {
        printf("IndexOutOfRangeException: The array is already full.\n");
        return 1;
    }
    unsigned short randomNum = 10 + rand() % 100;
    Person p1;
    strcpy(p1.name, name);
    strcpy(p1.birthDay, birthDay);
    strcpy(p1.birthMonth, birthMonth);
    p1.birthYear = birthYear;
    p1.gender = gender;

    strcpy(p1.id, birthDay);
    strcpy(p1.id, birthMonth);
    char *tempBirthYear = malloc(5 * sizeof(*tempBirthYear));
    strcpy(p1.id, sprintf(tempBirthYear, "%hu", birthYear));
    free(tempBirthYear);
    char *tempRandomNum = malloc(3 * sizeof(*tempBirthYear));
    strcpy(p1.id, sprintf(tempRandomNum, "%hu", randomNum));
    free(tempRandomNum);
    strcpy(p1.id, "\0");

    printf("%s\n", p1.id);
    *(personArr + index) = p1;
    index++;
    return 0;
}

int removePerson(char *id)
{
    for (size_t i = 0; i < PERSONARR_LEN; i++)
    {
        if (strcmp(personArr[i].id, id) == 0)
        {
            *(personArr + i) = *(personArr + index);
            index--;
            return 0;
        }
    }
    printf("No such person found in array.\n");
    return 1;
}

void readPerson()
{
    Person p1;
    printf("Enter a name: ");
    scanf("%s", p1.name);
    printf("Enter a birth day: ");
    scanf("%hhu", &p1.birthDay);
    printf("Enter a birth month: ");
    scanf("%hhu", &p1.birthMonth);
    printf("Enter a birth year: ");
    scanf("%hu", &p1.birthYear);
    printf("Enter gender ('m' for male, 'f' for female): ");
    scanf("%c", &p1.gender);
    if (addPerson(p1.name, p1.birthYear, p1.birthMonth, p1.birthDay, p1.gender) == 0)
        printf("Person added successfull!\n");
}

int printPerson(char *id)
{
    for (size_t i = 0; i < PERSONARR_LEN; i++)
    {
        if (strcmp(personArr[i].id, id) == 0)
        {
            printf("Name: %s\n", personArr[i].name);
            printf("Id: %s\n", personArr[i].id);
            printf("BirthDay: %hhu\n", personArr[i].birthDay);
            printf("BirthMonth: %hhu\n", personArr[i].birthMonth);
            printf("BirthYear: %hu\n", personArr[i].birthYear);
            printf("Gender: %d\n", personArr[i].gender);
            return 0;
        }
    }
    printf("No such person found in array.\n");
    return 1;
}

void printArr()
{
    for (size_t i = 0; i < PERSONARR_LEN; i++)
    {
        printf("Name: %s\n", personArr[i].name);
        printf("Id: %s\n", personArr[i].id);
        printf("BirthDay: %s\n", personArr[i].birthDay);
        printf("BirthMonth: %s\n", personArr[i].birthMonth);
        printf("BirthYear: %hu\n", personArr[i].birthYear);
        printf("Gender: %c\n", personArr[i].gender);
        printf("----------------");
    }
}
