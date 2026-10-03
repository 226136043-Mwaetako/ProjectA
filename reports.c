#include <stdio.h>
#include <string.h>
#include "reports.h"
#include "assets.h"

// ---------- Data from the other modules (declared in their files) ---------- */

/* Employees (EmployeeManagement.c) */
extern char  EmployeeName[][50];
extern float BasicSalary[];
extern float HousingAllowance[];
extern float TransportAllowance[];
extern int   NumberOfEmployees;

/* Budget (names assumed - change them to match the Budget module) */
#if HAS_BUDGET_MODULE
extern char  deptNames[][50];
extern float allocated[];
extern float expenditure[];
extern int   deptCount;
#endif

/* Suppliers (names assumed - change them to match the Supplier module) */
#if HAS_SUPPLIER_MODULE
extern char supIDs[][10];
extern char supNames[][100];
extern char supEmails[][100];
extern char supPhones[][30];
extern char supTowns[][50];
extern int  supCount;
#endif

/* Assets come from assets.h: assets[] and assetCount */

static void clearReportsInput(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static void reportHeader(const char title[]) {
    printf("\n========================================\n");
    printf(" %s\n", title);
    printf("========================================\n");
}

/* Gross salary of employee i = basic + housing + transport */
static float grossSalary(int i) {
    return BasicSalary[i] + HousingAllowance[i] + TransportAllowance[i];
}

void employeeReport(void) {
    reportHeader("EMPLOYEE REPORT");

    if (NumberOfEmployees == 0) {
        printf("No employees registered.\n");
        return;
    }

    float total = 0;
    int highest = 0;
    int lowest = 0;

    for (int i = 0; i < NumberOfEmployees; i++) {
        float salary = grossSalary(i);
        total += salary;

        if (salary > grossSalary(highest)) {
            highest = i;
        }
        if (salary < grossSalary(lowest)) {
            lowest = i;
        }
    }

    printf("Total Employees : %d\n", NumberOfEmployees);
    printf("Total Payroll   : N$%.2f\n", total);
    printf("Average Salary  : N$%.2f\n", total / NumberOfEmployees);
    printf("Highest Salary  : N$%.2f (%s)\n", grossSalary(highest), EmployeeName[highest]);
    printf("Lowest Salary   : N$%.2f (%s)\n", grossSalary(lowest), EmployeeName[lowest]);
}

void budgetReport(void) {
    reportHeader("BUDGET REPORT");

#if HAS_BUDGET_MODULE
    if (deptCount == 0) {
        printf("No budgets registered.\n");
        return;
    }

    float totalAllocated = 0;
    float totalSpent = 0;
    int exceeded = 0;

    printf("%-20s %14s %14s %14s  %s\n",
           "Department", "Allocated", "Expenditure", "Remaining", "Status");

    for (int i = 0; i < deptCount; i++) {
        float remaining = allocated[i] - expenditure[i];
        char status[20];

        totalAllocated += allocated[i];
        totalSpent += expenditure[i];

        if (remaining < 0) {
            strcpy(status, "OVER BUDGET");
            exceeded++;
        } else {
            strcpy(status, "WITHIN BUDGET");
        }

        printf("%-20s %14.2f %14.2f %14.2f  %s\n",
               deptNames[i], allocated[i], expenditure[i], remaining, status);
    }

    printf("\nTotal Allocated Budget : N$%.2f\n", totalAllocated);
    printf("Total Expenditure      : N$%.2f\n", totalSpent);
    printf("Remaining Budget       : N$%.2f\n", totalAllocated - totalSpent);

    printf("\nDepartments exceeding budget:\n");
    if (exceeded == 0) {
        printf("None.\n");
    } else {
        for (int i = 0; i < deptCount; i++) {
            if (expenditure[i] > allocated[i]) {
                printf("- %s (over by N$%.2f)\n",
                       deptNames[i], expenditure[i] - allocated[i]);
            }
        }
    }
#else
    printf("Budget module is not connected yet.\n");
#endif
}

void supplierReport(void) {
    reportHeader("SUPPLIER REPORT");

#if HAS_SUPPLIER_MODULE
    if (supCount == 0) {
        printf("No suppliers registered.\n");
        return;
    }

    printf("%-8s %-22s %-26s %-14s %-12s\n",
           "ID", "Name", "Email", "Phone", "Town");

    for (int i = 0; i < supCount; i++) {
        printf("%-8s %-22s %-26s %-14s %-12s\n",
               supIDs[i], supNames[i], supEmails[i], supPhones[i], supTowns[i]);
    }

    printf("\nTotal Suppliers: %d\n", supCount);
#else
    printf("Supplier module is not connected yet.\n");
#endif
}

void assetReport(void) {
    reportHeader("ASSET REPORT");

    if (assetCount == 0) {
        printf("No assets registered.\n");
        return;
    }

    double totalValue = 0;

    printf("%-10s %-20s %-12s %12s %-15s %-10s\n",
           "ID", "Name", "Type", "Value (N$)", "Department", "Condition");

    for (int i = 0; i < assetCount; i++) {
        totalValue += assets[i].purchaseValue;

        printf("%-10s %-20s %-12s %12.2f %-15s %-10s\n",
               assets[i].assetID, assets[i].assetName, assets[i].assetType,
               assets[i].purchaseValue, assets[i].department, assets[i].condition);
    }

    printf("\nTotal Assets : %d\n", assetCount);
    printf("Total Value  : N$%.2f\n", totalValue);
}

void displayReports(void) {
    int choice = -1;

    do {
        printf("\n===== REPORTS =====\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            choice = -1;
        }
        clearReportsInput();

        switch (choice) {
            case 1:
                employeeReport();
                break;
            case 2:
                budgetReport();
                break;
            case 3:
                supplierReport();
                break;
            case 4:
                assetReport();
                break;
            case 5:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
}