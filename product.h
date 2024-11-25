#ifndef PRODUCT_H
#define PRODUCT_H

typedef struct {
    int id;
    char name[50];
    int quantity;
    float price;
} Product;

void addProduct();
void updateProduct();
void deleteProduct();
void viewInventory();
void searchProductByName();
void exportToCSV();

#endif
