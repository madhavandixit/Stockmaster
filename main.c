/*Project Name : StockMaster
Description : Manage inventory for a small business, including product details, stock levels and sales record
Features : Add, update, delete product records, track inventory, manage sales transactions
UI elements : console based forms for product entry, inventory lists, sales transaction forms*/


#include <stdio.h>
#include <stdlib.h>
#include "product.h"
#include "product.c"
#include "sales.h"
#include "sales.c"
#include "utils.h"
#include "utils.c"
#include "analytics.h"
#include "analytics.c"

void adminMenu(void){
    int choice;
    do {
        printf("\n==== Admin Menu ====\n");
        printf("1. Add Product\n");
        printf("2. Update Product\n");
        printf("3. Delete Product\n");
        printf("4. View Inventory\n");
        printf("5. Search Product\n");
        printf("6. Record Sale\n");
        printf("7. Export Inventory to CSV\n");
        printf("8. View Reports\n");
        printf("9. Backup Data\n");
        printf("10. Restore Data\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addProduct(); break;
            case 2: updateProduct(); break;
            case 3: deleteProduct(); break;
            case 4: viewInventory(); break;
            case 5: searchProductByName(); break;
            case 6: recordSale(); break;
            case 7: exportToCSV(); break;
            case 8: generateReports(); break;
            case 9: backupData(); break;
            case 10: restoreData(); break;
            case 11: printf("Exiting admin menu...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 11);
}

void userMenu() {
    int choice;
    do {
        printf("\n==== User Menu ====\n");
        printf("1. View Inventory\n");
        printf("2. Search Product\n");
        printf("3. Record Sale\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: viewInventory(); break;
            case 2: searchProductByName(); break;
            case 3: recordSale(); break;
            case 4: printf("Exiting user menu...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 4);
}

int main() {
    int role;
    initializeFiles();

    printf("==== StockMaster Login ====\n");
    printf("Enter role (1-Admin, 2-User): ");
    scanf("%d", &role);

    if (role == 1) {
        adminMenu();
    } else if (role == 2) {
        userMenu();
    } else {
        printf("Invalid role! Exiting...\n");
    }

    return 0;
}
