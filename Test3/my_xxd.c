#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printHexDump(FILE *file);
void printBinary(FILE *file);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Wrong number of arguments.\n");
        return 1;
    }

    const char *filename = argv[1];
    const char *print_mode = argv[2];

    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    if (strcmp(print_mode, "-H") == 0)
        printHexDump(file);

    else if (strcmp(print_mode, "-B") == 0)
        printBinary(file);

    else
        printf("Invalid print mode.\n");

    fclose(file);

    return 0;
}

void printHexDump(FILE *file)
{
    int offset = 0;
    unsigned char buffer[16];
    size_t read_bytes;

    while ((read_bytes = fread(buffer, sizeof(*buffer), sizeof(buffer), file)) > 0)
    {
        printf("%08x: ", offset);

        for (size_t i = 0; i < read_bytes; i++)
        {
            printf("%02x ", buffer[i]);
            if (i == 7)
                printf(" ");
        }

        for (size_t i = read_bytes; i < sizeof(buffer); i++)
        {
            printf("   ");
            if (i == 7)
                printf(" ");
        }

        printf("\n");

        for (size_t i = 0; i < read_bytes; i++)
        {
            if (buffer[i] >= ' ' && buffer[i] <= 'z')
                printf("%c", buffer[i]);
            else
                printf(".");
        }

        printf("\n");

        offset += read_bytes;
    }
}

void printBinary(FILE *file)
{
    int c;
    while ((c = fgetc(file)) != EOF)
    {
        for (int i = 7; i >= 0; i--)
        {
            printf("%d", (c >> i) & 1);
        }
        printf(" ");
    }
    printf("\n");
}
