#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"

// Add a new product to the inventory
void addProduct() {
    Product newProduct;
    FILE *file = fopen("products.dat", "ab");

    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter product details:\n");
    printf("ID: ");
    scanf("%d", &newProduct.id);
    printf("Name: ");
    scanf(" %[^\n]", newProduct.name);
    printf("Quantity: ");
    scanf("%d", &newProduct.quantity);
    printf("Price: ");
    scanf("%f", &newProduct.price);

    fwrite(&newProduct, sizeof(Product), 1, file);
    fclose(file);

    printf("Product added successfully!\n");
}

// View all products in the inventory
void viewInventory() {
    Product product;
    FILE *file = fopen("products.dat", "rb");

    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    printf("\n=== Inventory ===\n");
    printf("ID\tName\t\tQuantity\tPrice\n");

    while (fread(&product, sizeof(Product), 1, file)) {
        printf("%d\t%s\t\t%d\t\t%.2f\n", product.id, product.name, product.quantity, product.price);
    }

    fclose(file);
}

// Search for a product by its name
void searchProductByName() {
    char searchName[50];
    Product product;
    FILE *file = fopen("products.dat", "rb");

    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter product name to search: ");
    scanf(" %[^\n]", searchName);

    printf("\n=== Search Results ===\n");
    int found = 0;
    while (fread(&product, sizeof(Product), 1, file)) {
        if (strstr(product.name, searchName)) {
            printf("ID: %d, Name: %s, Quantity: %d, Price: %.2f\n",
                   product.id, product.name, product.quantity, product.price);
            found = 1;
        }
    }
    fclose(file);

    if (!found) {
        printf("No products found with the name '%s'.\n", searchName);
    }
}

// Export inventory to a CSV file
void exportToCSV() {
    Product product;
    FILE *inputFile = fopen("products.dat", "rb");
    FILE *outputFile = fopen("inventory.csv", "w");

    if (!inputFile || !outputFile) {
        printf("Error opening files.\n");
        return;
    }

    fprintf(outputFile, "ID,Name,Quantity,Price\n");

    while (fread(&product, sizeof(Product), 1, inputFile)) {
        fprintf(outputFile, "%d,%s,%d,%.2f\n",
                product.id, product.name, product.quantity, product.price);
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Inventory exported to inventory.csv successfully!\n");
}

// Update the details of an existing product
void updateProduct() {
    int productId, found = 0;
    FILE *file = fopen("products.dat", "r+b");  // Open in read and write mode
    Product product;

    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter Product ID to update: ");
    scanf("%d", &productId);

    // Search for the product by ID
    while (fread(&product, sizeof(Product), 1, file)) {
        if (product.id == productId) {
            found = 1;
            printf("Product found! Enter new details.\n");

            // Update the product details
            printf("New Name: ");
            scanf(" %[^\n]", product.name);
            printf("New Quantity: ");
            scanf("%d", &product.quantity);
            printf("New Price: ");
            scanf("%f", &product.price);

            // Move the file pointer back to the start of the current product and update it
            fseek(file, -sizeof(Product), SEEK_CUR);
            fwrite(&product, sizeof(Product), 1, file);
            printf("Product updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Product not found!\n");
    }

    fclose(file);
}

// Delete a product from the inventory
void deleteProduct() {
    int productId, found = 0;
    FILE *file = fopen("products.dat", "r+b");  // Open for reading and writing
    FILE *tempFile = fopen("temp.dat", "w+b");  // Temporary file to store remaining products
    Product product;

    if (!file || !tempFile) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter Product ID to delete: ");
    scanf("%d", &productId);

    // Search for the product by ID and copy all non-deleted products to the temp file
    while (fread(&product, sizeof(Product), 1, file)) {
        if (product.id == productId) {
            found = 1;
            printf("Product found! Deleting...\n");
        } else {
            fwrite(&product, sizeof(Product), 1, tempFile);
        }
    }

    if (!found) {
        printf("Product not found!\n");
    } else {
        // Replace the original file with the temp file
        fclose(file);
        fclose(tempFile);
        remove("products.dat");
        rename("temp.dat", "products.dat");
        printf("Product deleted successfully!\n");
    }
}
