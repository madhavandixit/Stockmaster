#ifndef SALES_H
#define SALES_H

typedef struct {
    int productId;
    int quantitySold;
    char date[11]; // Format: YYYY-MM-DD
    float totalPrice;
} SalesRecord;

void recordSale();

#endif
