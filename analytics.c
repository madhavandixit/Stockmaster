#include <stdio.h>
#include <string.h>
#include "product.h"
#include "sales.h"

void generateReports() {
    FILE *productFile = fopen("products.dat", "rb");
    FILE *salesFile = fopen("sales.dat", "rb");

    if (!productFile || !salesFile) {
        printf("Error opening files for reports.\n");
        return;
    }

    printf("\n==== Reports ====\n");
    printf("1. Top-Selling Products\n");
    printf("2. Revenue Trends\n");
    printf("3. Low Stock Items\n");

    fclose(productFile);
    fclose(salesFile);
}
