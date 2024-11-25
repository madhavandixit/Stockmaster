#include <stdio.h>
#include <stdlib.h>
#include "sales.h"
#include "product.h"

void recordSale() {
    SalesRecord sale;
    Product product;
    FILE *productFile = fopen("products.dat", "rb+");
    FILE *salesFile = fopen("sales.dat", "ab");

    if (!productFile || !salesFile) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter product ID: ");
    scanf("%d", &sale.productId);

    int found = 0;
    while (fread(&product, sizeof(Product), 1, productFile)) {
        if (product.id == sale.productId) {
            found = 1;

            printf("Enter quantity sold: ");
            scanf("%d", &sale.quantitySold);

            if (sale.quantitySold > product.quantity) {
                printf("Not enough stock available!\n");
                fclose(productFile);
                fclose(salesFile);
                return;
            }

            product.quantity -= sale.quantitySold;

            fseek(productFile, -sizeof(Product), SEEK_CUR);
            fwrite(&product, sizeof(Product), 1, productFile);

            printf("Enter sale date (YYYY-MM-DD): ");
            scanf(" %[^\n]", sale.date);

            sale.totalPrice = sale.quantitySold * product.price;
            fwrite(&sale, sizeof(SalesRecord), 1, salesFile);

            printf("Sale recorded successfully! Total Price: %.2f\n", sale.totalPrice);
            break;
        }
    }

    if (!found) {
        printf("Product not found!\n");
    }

    fclose(productFile);
    fclose(salesFile);
}
