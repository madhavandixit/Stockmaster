#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void initializeFiles() {
    FILE *file;

    file = fopen("products.dat", "ab");
    if (file) fclose(file);

    file = fopen("sales.dat", "ab");
    if (file) fclose(file);

    file = fopen("error.log", "a");
    if (file) fclose(file);
}

void backupData() {
    char command[100];
    sprintf(command, "cp products.dat backup_products.dat");
    system(command);

    sprintf(command, "cp sales.dat backup_sales.dat");
    system(command);

    printf("Data backup completed successfully!\n");
}

void restoreData() {
    char command[100];
    sprintf(command, "cp backup_products.dat products.dat");
    system(command);

    sprintf(command, "cp backup_sales.dat sales.dat");
    system(command);

    printf("Data restored from backup successfully!\n");
}

void logError(const char *message) {
    FILE *logFile = fopen("error.log", "a");
    if (logFile) {
        fprintf(logFile, "Error: %s\n", message);
        fclose(logFile);
    }
}
