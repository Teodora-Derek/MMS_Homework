#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ID_LEN 10
#define MAX_PEOPLE 10

typedef struct Person
{
    char name[100];
    char id[ID_LEN + 1];
    unsigned short birthYear;
    unsigned char birthMonth;
    unsigned char birthDay;
    char gender;
} Person;

Person **peopleArray;
size_t numPeople;

Person **initArray(size_t capacity);
Person *findPerson(char *id);
void readPerson();
char *generateId(unsigned char birthMonth, unsigned char birthDay);
int addPerson(char *name, unsigned short birthYear, unsigned char birthMonth, unsigned char birthDay, char gender);
int removePerson(char *id);
int printPerson(char *id);

int main(void)
{
    peopleArray = initArray(MAX_PEOPLE);
    for (size_t i = 0; i < 1; i++)
        readPerson();

    for (size_t i = 0; i < numPeople; i++)
        printPerson(peopleArray[i]->id);

    for (size_t i = 0; i < numPeople; i++)
        free(peopleArray[i]);
    free(peopleArray);

    return 0;
}

Person **initArray(size_t capacity)
{
    return malloc(capacity * sizeof(Person *));
}

char *generateId(unsigned char birthMonth, unsigned char birthDay)
{
    int random = 10 + rand() % 90;
    char *id = (char *)malloc(sizeof(char) * (ID_LEN + 1));
    snprintf(id, ID_LEN + 1, "%hhu%hhu%d", birthMonth, birthDay, random);
    return id;
}

Person *findPerson(char *id)
{
    for (size_t i = 0; i < numPeople; i++)
        if (strcmp(peopleArray[i]->id, id) == 0)
            return peopleArray[i];
    printf("No such person found.\n");
    return NULL;
}

int addPerson(char *name, unsigned short birthYear, unsigned char birthMonth, unsigned char birthDay, char gender)
{
    if (numPeople >= MAX_PEOPLE)
    {
        printf("The array of people is full.\n");
        return -1;
    }

    char *id = generateId(birthMonth, birthDay);
    Person *newPerson = malloc(sizeof(Person));
    if (newPerson == NULL)
    {
        free(id);
        return -1;
    }

    strncpy(newPerson->name, name, sizeof(newPerson->name));
    strncpy(newPerson->id, id, sizeof(newPerson->id));
    newPerson->birthYear = birthYear;
    newPerson->birthMonth = birthMonth;
    newPerson->birthDay = birthDay;
    newPerson->gender = gender;

    peopleArray[numPeople++] = newPerson;
    free(id);
    return 0;
}

int removePerson(char *id)
{
    Person *person = findPerson(id);
    if (person == NULL)
        return -1;

    size_t targetIdx = 0;
    for (size_t i = 0; i < numPeople; i++)
    {
        if (strcmp(peopleArray[i]->id, id) == 0)
        {
            targetIdx = i;
            break;
        }
    }

    free(peopleArray[targetIdx]);
    for (size_t i = targetIdx; i < numPeople - 1; i++)
        peopleArray[i] = peopleArray[i + 1];
    numPeople--;
    return 0;
}

void readPerson()
{
    char name[100];
    unsigned short birthYear;
    unsigned char birthMonth, birthDay;
    char gender;

    printf("Enter name: ");
    scanf("%s", name);
    printf("Enter birth year, month, and day: ");
    scanf("%hu %hhu %hhu", &birthYear, &birthMonth, &birthDay);
    printf("Enter gender (M/F): ");
    scanf(" %c", &gender);

    if (addPerson(name, birthYear, birthMonth, birthDay, gender) == 0)
        printf("Person added successfully.\n");
    else
        printf("Failed to add person.\n");
}

int printPerson(char *id)
{
    Person *person = findPerson(id);
    if (person == NULL)
        return -1;

    printf("Name: %s\n", person->name);
    printf("ID: %s\n", person->id);
    printf("Birth year: %hu\n", person->birthYear);
    printf("Birth month: %hhu\n", person->birthMonth);
    printf("Birth day: %hhu\n", person->birthDay);
    printf("Gender: %c\n", person->gender);
    return 0;
}
