#include <stdio.h>
#include "validation.h"
#include "employees.h"
#include "budget.h"
#include "supplier.h"
#include "assets.h"
#include "reports.h"

int main(void) {
    int choice;

    do {
        printf("\n========================================\n");
        printf(" MUNICIPAL FINANCIAL MANAGEMENT SYSTEM \n");
        printf("========================================\n");
        printf("1. Employee Management\n");
        printf("2. Budget Management\n");
        printf("3. Supplier Management\n");
        printf("4. Asset Management\n");
        printf("5. Reports\n");
        printf("6. Exit\n");
        printf("========================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            choice = -1; 
        }
        clearInputBuffer(); 

        switch (choice) {
            case 1: employeeMenu(); break;
            case 2: budgetMenu(); break; 
            case 3: SupplierMenu(); break; 
            case 4: assetMenu(); break;
            case 5: displayReports(); break; 
            case 6: printf("\nExiting system. Goodbye!\n"); break;
            default: printf("\nInvalid selection! Choose between 1 and 6.\n");
        }
    } while (choice != 6);

    return 0;
}
