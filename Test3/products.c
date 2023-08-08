#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PRODUCT_NAME_LENGTH 50
#define NUM_PRODUCTS 40

typedef struct Product
{
    double old_price;
    double new_price;
    unsigned int id;
    char product_type;
    char product_name[MAX_PRODUCT_NAME_LENGTH];
} Product;

int compareProducts(const void *a, const void *b)
{
    const Product *productA = (const Product *)a;
    const Product *productB = (const Product *)b;

    double priceIncreaseA = productA->new_price - productA->old_price;
    double priceIncreaseB = productB->new_price - productB->old_price;

    if (priceIncreaseA != priceIncreaseB)
        return priceIncreaseB - priceIncreaseA;

    else if (productA->product_type != productB->product_type)
        return productB->product_type - productA->product_type;

    else if (strcmp(productA->product_name, productB->product_name) != 0)
        return strcmp(productA->product_name, productB->product_name);

    else
        return productA->id - productB->id;
}

void writeProductsToFile(Product *products, const char *filename)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        perror("Error opening file for writing");
        exit(1);
    }

    fwrite(products, sizeof(Product), NUM_PRODUCTS, file);

    fclose(file);
}

void readProductsFromFile(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        perror("Error opening file for reading");
        exit(1);
    }

    Product products[NUM_PRODUCTS];
    fread(products, sizeof(Product), NUM_PRODUCTS, file);

    fclose(file);

    for (int i = 0; i < NUM_PRODUCTS; i++)
    {
        printf("Product %d:\n", i + 1);
        printf("Old Price: %.2lf\n", products[i].old_price);
        printf("New Price: %.2lf\n", products[i].new_price);
        printf("ID: %u\n", products[i].id);
        printf("Product Type: %c\n", products[i].product_type);
        printf("Product Name: %s\n\n", products[i].product_name);
    }
}

int main(void)
{
    srand(time(NULL));
    const char *productNames[] = {"Product A", "Product B", "Product C", "Product D"};

    Product products[NUM_PRODUCTS];

    for (int i = 0; i < NUM_PRODUCTS; i++)
    {
        products[i].old_price = 4.99 + (rand() % 955) / 100.0;
        products[i].new_price = 4.99 + (rand() % 955) / 100.0;
        products[i].id = i + 1;
        products[i].product_type = 'A' + rand() % 4;
        strcpy(products[i].product_name, productNames[rand() % 4]);
    }

    printf("Array of Products before sorting:\n");
    for (int i = 0; i < NUM_PRODUCTS; i++)
    {
        printf("Product %d:\n", i + 1);
        printf("Old Price: %.2lf\n", products[i].old_price);
        printf("New Price: %.2lf\n", products[i].new_price);
        printf("ID: %u\n", products[i].id);
        printf("Product Type: %c\n", products[i].product_type);
        printf("Product Name: %s\n\n", products[i].product_name);
    }

    qsort(products, NUM_PRODUCTS, sizeof(Product), compareProducts);

    printf("Array of Products after sorting:\n");
    for (int i = 0; i < NUM_PRODUCTS; i++)
    {
        printf("Product %d:\n", i + 1);
        printf("Old Price: %.2lf\n", products[i].old_price);
        printf("New Price: %.2lf\n", products[i].new_price);
        printf("ID: %u\n", products[i].id);
        printf("Product Type: %c\n", products[i].product_type);
        printf("Product Name: %s\n\n", products[i].product_name);
    }

    writeProductsToFile(products, "products.bin");
    printf("Products written to 'products.bin'\n");

    printf("Reading products from file:\n");
    readProductsFromFile("products.bin");

    return 0;
}
