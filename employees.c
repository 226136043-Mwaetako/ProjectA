#include <stdio.h>
#include <string.h>
#include "employees.h"
#include "validation.h"

#define max_Employees 50

// Made global (non-static) so reports.c can calculate averages
char  EmployeeName[max_Employees][50];
char  EmployeeID[max_Employees][10];
char  Department[max_Employees][50];
float BasicSalary[max_Employees];
float HousingAllowance[max_Employees];
float TransportAllowance[max_Employees];
char  PhoneNumber[max_Employees][15];
char  EmployeeEmail[max_Employees][50];
int   NumberOfEmployees = 0;

static float calculateSalary(float basic, float housing, float transport) {
    return basic + housing + transport;
}

static void printEmployee(int i) {
    printf("Employee Name: %s\n", EmployeeName[i]);
    printf("Employee ID: %s\n", EmployeeID[i]);
    printf("Department: %s\n", Department[i]);
    printf("Basic Salary: N$%.2f\n", BasicSalary[i]);
    printf("Housing Allowance: N$%.2f\n", HousingAllowance[i]);
    printf("Transport Allowance: N$%.2f\n", TransportAllowance[i]);
    printf("Phone Number: %s\n", PhoneNumber[i]);
    printf("Employee Email: %s\n", EmployeeEmail[i]);
}

void AddEmployee(void) {
    if (NumberOfEmployees >= max_Employees) {
        printf("Maximum number of employees reached.\n");
        return;
    }
    int n = NumberOfEmployees;

    readNonEmptyString("Enter Employee Name: ", EmployeeName[n], 50);
    readNonEmptyString("Enter Employee ID: ", EmployeeID[n], 10);
    readNonEmptyString("Enter Department: ", Department[n], 50);

    BasicSalary[n]        = readNonNegativeFloat("Enter Basic Salary: ");
    HousingAllowance[n]   = readNonNegativeFloat("Enter Housing Allowance: ");
    TransportAllowance[n] = readNonNegativeFloat("Enter Transport Allowance: ");

    readNonEmptyString("Enter Phone Number: ", PhoneNumber[n], 15);
    readNonEmptyString("Enter Employee Email: ", EmployeeEmail[n], 50);

    NumberOfEmployees++;
    printf("Employee added successfully.\n");
}

void displayEmployeeDetails(void) {
    if (NumberOfEmployees == 0) {
        printf("\nNo employees registered.\n");
        return;
    }
    printf("\nEmployee Details:\n");
    for (int i = 0; i < NumberOfEmployees; i++) {
        printf("\n=================Employee %d==================\n", i + 1);
        printEmployee(i);
        printf("===============================================\n");
    }
}

void SearchEmployee(void) {
    char searchID[10];
    int found = 0;

    readNonEmptyString("Enter Employee ID to search: ", searchID, 10);

    for (int i = 0; i < NumberOfEmployees; i++) {
        if (strcmp(EmployeeID[i], searchID) == 0) {
            printf("\nEmployee Found:\n");
            printEmployee(i);
            found = 1;
            break;
        }
    }
    if (!found) printf("Employee with ID %s not found.\n", searchID);
}

void CalculateBasicSalary(void) {
    char searchID[10];
    int found = 0;

    readNonEmptyString("Enter Employee ID to calculate salary: ", searchID, 10);

    for (int i = 0; i < NumberOfEmployees; i++) {
        if (strcmp(EmployeeID[i], searchID) == 0) {
            float totalSalary = calculateSalary(BasicSalary[i], HousingAllowance[i], TransportAllowance[i]);
            printf("Gross Salary for Employee ID %s: N$%.2f\n", searchID, totalSalary);
            found = 1;
            break;
        }
    }
    if (!found) printf("Employee with ID %s not found.\n", searchID);
}

void employeeMenu(void) {
    int choice;
    do {
        printf("\n===== EMPLOYEE MANAGEMENT =====\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Calculate Salary\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) choice = -1;
        clearInputBuffer();

        switch (choice) {
            case 1: AddEmployee(); break;
            case 2: displayEmployeeDetails(); break;
            case 3: SearchEmployee(); break;
            case 4: CalculateBasicSalary(); break;
            case 5: break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);
}
