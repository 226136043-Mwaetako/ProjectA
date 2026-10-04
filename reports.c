#include <stdio.h>
#include <string.h>
#include "reports.h"
#include "assets.h"
#include "supplier.h"
#include "validation.h"

/* Extern configurations linked to array variables */
extern char  EmployeeName[][50];
extern float BasicSalary[];
extern float HousingAllowance[];
extern float TransportAllowance[];
extern int   NumberOfEmployees;

extern char  deptName[][45];
extern float allocated[];
extern float expenditure[];
extern int   deptCount;

static void reportHeader(const char title[]) {
    printf("\n========================================\n");
    printf(" %s\n", title);
    printf("========================================\n");
}

static float grossSalary(int i) {
    return BasicSalary[i] + HousingAllowance[i] + TransportAllowance[i];
}

void employeeReport(void) {
    reportHeader("EMPLOYEE REPORT");
    if (NumberOfEmployees == 0) { printf("No employees registered.\n"); return; }
    
    float total = 0; int hi = 0, lo = 0;
    for (int i = 0; i < NumberOfEmployees; i++) {
        float s = grossSalary(i); total += s;
        if (s > grossSalary(hi)) hi = i;
        if (s < grossSalary(lo)) lo = i;
    }
    printf("Total Employees : %d\n", NumberOfEmployees);
    printf("Total Payroll   : N$%.2f\n", total);
    printf("Average Salary  : N$%.2f\n", total / NumberOfEmployees);
    printf("Highest Salary  : N$%.2f (%s)\n", grossSalary(hi), EmployeeName[hi]);
    printf("Lowest Salary   : N$%.2f (%s)\n", grossSalary(lo), EmployeeName[lo]);
}

void budgetReport(void) {
    reportHeader("BUDGET REPORT");
    if (deptCount == 0) { printf("No budgets registered.\n"); return; }
    
    float tAlloc = 0, tSpent = 0; int ex = 0;
    printf("%-20s %14s %14s %14s  %s\n", "Department", "Allocated", "Expenditure", "Remaining", "Status");
    
    for (int i = 0; i < deptCount; i++) {
        float rem = allocated[i] - expenditure[i];
        tAlloc += allocated[i]; tSpent += expenditure[i];
        if (rem < 0) ex++;
        printf("%-20s %14.2f %14.2f %14.2f  %s\n", deptName[i], allocated[i], expenditure[i], rem, (rem < 0) ? "OVER BUDGET" : "WITHIN BUDGET");
    }
    printf("\nTotal Allocated Budget : N$%.2f\nTotal Expenditure      : N$%.2f\nRemaining Budget       : N$%.2f\n", tAlloc, tSpent, tAlloc - tSpent);
}

void supplierReport(void) {
    reportHeader("SUPPLIER REPORT");
    if (supCount == 0) { printf("No suppliers registered.\n"); return; }
    printf("%-6s %-20s %-25s %-15s %-12s\n", "ID", "Name", "Email", "Phone", "Town");
    for (int i = 0; i < supCount; i++) {
        printf("%-6d %-20s %-25s %-15s %-12s\n", supID[i], supName[i], supEmail[i], supPhone[i], supTown[i]);
    }
    printf("\nTotal Suppliers: %d\n", supCount);
}

void assetReport(void) {
    reportHeader("ASSET REPORT");
    if (assetCount == 0) { printf("No assets registered.\n"); return; }
    double totalValue = 0;
    printf("%-10s %-20s %-12s %12s %-15s %-10s\n", "ID", "Name", "Type", "Value (N$)", "Department", "Condition");
    for (int i = 0; i < assetCount; i++) {
        totalValue += assets[i].purchaseValue;
        printf("%-10s %-20s %-12s %12.2f %-15s %-10s\n", assets[i].assetID, assets[i].assetName, assets[i].assetType, assets[i].purchaseValue, assets[i].department, assets[i].condition);
    }
    printf("\nTotal Assets : %d\nTotal Value  : N$%.2f\n", assetCount, totalValue);
}

void displayReports(void) {
    int choice = -1;
    do {
        printf("\n===== REPORTS =====\n1. Employee Report\n2. Budget Report\n3. Supplier Report\n4. Asset Report\n5. Back to Main Menu\nEnter choice: ");
        if (scanf("%d", &choice) != 1) choice = -1;
        clearInputBuffer();
        switch (choice) {
            case 1: employeeReport(); break;
            case 2: budgetReport(); break;
            case 3: supplierReport(); break;
            case 4: assetReport(); break;
            default: break;
        }
    } while (choice != 5);
}
