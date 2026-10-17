/*
 * main.c - Municipal Financial Management System (MFMS)
 * PAP521S Project A, Group 21
 *
 * Shows the main menu and calls the menu function of each module.
 * All the real work is done inside the modules, not here.
 */

#include <stdio.h>
#include "EmployeeManagement.h"
#include "budget.h"
#include "supplier.h"
#include "assets.h"
#include "reports.h"

/* Prints the main menu. */
void displayMenu(void) {
    printf("\n========================================\n");
    printf(" MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("1. Employee Management\n");
    printf("2. Budget Management\n");
    printf("3. Supplier Management\n");
    printf("4. Asset Management\n");
    printf("5. Reports\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

/* Repeats the menu until the user chooses 6 (Exit). */
int main(void) {
    int choice = -1;
    int c;

    do {
        displayMenu();

        /* Text or other non-numeric input counts as an invalid choice. */
        if (scanf("%d", &choice) != 1) {
            choice = -1;
        }
        while ((c = getchar()) != '\n' && c != EOF) {
        }

        switch (choice) {
            case 1:
                employeeMenu();
                break;
            case 2:
                budgetMenu();
                break;
            case 3:
                SupplierMenu();
                break;
            case 4:
                assetMenu();
                break;
            case 5:
                displayReports();
                break;
            case 6:
                printf("Goodbye.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
