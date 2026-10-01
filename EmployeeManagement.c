#include <stdio.h>
#include <string.h>

#define max_Employees 50

char  EmployeeName[max_Employees][50];
char  EmployeeID[max_Employees][10];
char  Department[max_Employees][50];

float BasicSalary[max_Employees];
float HousingAllowance[max_Employees];
float TransportAllowance[max_Employees];
char  PhoneNumber[max_Employees][15];
char  EmployeeEmail[max_Employees][50];

int   NumberOfEmployees = 0;

void  clearInputBuffer(void);
float readNonNegativeFloat(const char prompt[]);
float calculateSalary(float basic, float housing, float transport);
void  printEmployee(int i);
void  AddEmployee(void);
void  displayEmployeeDetails(void);
void  SearchEmployee(void);
void  CalculateBasicSalary(void);

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

float readNonNegativeFloat(const char prompt[]) {
    float value = 0;
    int ok;

    do {
        printf("%s", prompt);
        ok = scanf(" %f", &value);
        clearInputBuffer();

        if (ok != 1) {
            printf("Invalid input. Please enter a number.\n");
        } else if (value < 0) {
            printf("Value cannot be negative.\n");
            ok = 0;
        }
    } while (ok != 1);

    return value;
}

float calculateSalary(float basic, float housing, float transport) {
    return basic + housing + transport;
}

void printEmployee(int i) {
    printf("Employee Name: %s\n", EmployeeName[i]);
    printf("Employee ID: %s\n", EmployeeID[i]);
    printf("Department: %s\n", Department[i]);
    printf("Basic Salary: %.2f\n", BasicSalary[i]);
    printf("Housing Allowance: %.2f\n", HousingAllowance[i]);
    printf("Transport Allowance: %.2f\n", TransportAllowance[i]);
    printf("Phone Number: %s\n", PhoneNumber[i]);
    printf("Employee Email: %s\n", EmployeeEmail[i]);
}

void AddEmployee(void) {
    if (NumberOfEmployees >= max_Employees) {
        printf("Maximum number of employees reached.\n");
        return;
    }

    int n = NumberOfEmployees;

    do {
        printf("Enter Employee Name: ");
        fgets(EmployeeName[n], sizeof(EmployeeName[n]), stdin);
        EmployeeName[n][strcspn(EmployeeName[n], "\n")] = '\0';

        if (strlen(EmployeeName[n]) == 0) {
            printf("Name cannot be empty.\n");
        }
    } while (strlen(EmployeeName[n]) == 0);

    printf("Enter Employee ID: ");
    scanf(" %9[^\n]", EmployeeID[n]);
    clearInputBuffer();

    printf("Enter Department: ");
    scanf(" %49[^\n]", Department[n]);
    clearInputBuffer();

    BasicSalary[n]        = readNonNegativeFloat("Enter Basic Salary: ");
    HousingAllowance[n]   = readNonNegativeFloat("Enter Housing Allowance: ");
    TransportAllowance[n] = readNonNegativeFloat("Enter Transport Allowance: ");

    printf("Enter Phone Number: ");
    scanf(" %14[^\n]", PhoneNumber[n]);
    clearInputBuffer();

    printf("Enter Employee Email: ");
    scanf(" %49[^\n]", EmployeeEmail[n]);
    clearInputBuffer();

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

    printf("Enter Employee ID to search: ");
    scanf(" %9s", searchID);
    clearInputBuffer();

    for (int i = 0; i < NumberOfEmployees; i++) {
        if (strcmp(EmployeeID[i], searchID) == 0) {
            printf("\nEmployee Found:\n");
            printEmployee(i);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %s not found.\n", searchID);
    }
}

void CalculateBasicSalary(void) {
    char searchID[10];
    int found = 0;

    printf("Enter Employee ID to calculate salary: ");
    scanf(" %9s", searchID);
    clearInputBuffer();

    for (int i = 0; i < NumberOfEmployees; i++) {
        if (strcmp(EmployeeID[i], searchID) == 0) {
            float totalSalary = calculateSalary(BasicSalary[i],
                                                HousingAllowance[i],
                                                TransportAllowance[i]);
            printf("Gross Salary for Employee ID %s: %.2f\n", searchID, totalSalary);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %s not found.\n", searchID);
    }
}

int main(void) {
    int choice;

    do {
        printf("\nEmployee Management System\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Calculate Salary\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            choice = -1;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                AddEmployee();
                break;
            case 2:
                displayEmployeeDetails();
                break;
            case 3:
                SearchEmployee();
                break;
            case 4:
                CalculateBasicSalary();
                break;
            case 5:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}