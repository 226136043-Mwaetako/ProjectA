#include <stdio.h>
#include <string.h>

#define max_Employees 50
//shows the maximum number of employees that can be stored in the system

char  EmployeeName[max_Employees][50];
char  EmployeeID[max_Employees][10];
char  Department[max_Employees][50];

float BasicSalary[max_Employees];
float HousingAllowance[max_Employees];
float TransportAllowance[max_Employees];
char  PhoneNumber[max_Employees][15];
char  EmployeeEmail[max_Employees][50];

int   NumberOfEmployees = 0;
// keeps track of the number of employees currently stored in the system
// starts at 0 and increments as new employees are added


// Function prototypes that tell the compiler about the functions that will be used later in the code
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
//clear input buffer to avoid any leftover and unwanted characters from previous inputs that could interfere with the next input operation
// is useful after using scanf() to read input, as it leaves the newline character in the input buffer


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
// This function prompts the user to enter a non-negative float value. It keeps asking until a valid input is provided. It also clears the input buffer after each attempt to avoid any leftover characters that could interfere with the next input operation.

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
// This function prints the details of an employee at index i in the arrays. It displays the employee's name, ID, department, salary components, phone number, and email.

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
// we use fgets() and strlen() to read the employee name and ensure it is not empty. The other details are read using scanf() with appropriate format specifiers. After successfully adding the employee, we increment the NumberOfEmployees counter.
}
// This function adds a new employee to the system. It prompts the user for various details, including name, ID, department, salary components, phone number, and email. It ensures that the name is not empty and that the salary components are non-negative. After successfully adding the employee, it increments the NumberOfEmployees counter.

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
// This function displays the details of all registered employees. If there are no employees, it informs the user. Otherwise, it iterates through the employee arrays and prints each employee's details using the printEmployee function.

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
// This function searches for an employee by their ID. It prompts the user to enter an ID and then iterates through the EmployeeID array to find a match. If found, it prints the employee's details; otherwise, it informs the user that the employee was not found.

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
// This function calculates the gross salary of an employee based on their ID. It prompts the user for an ID, searches for the employee, and if found, calculates the total salary using the calculateSalary function. It then displays the gross salary; if the employee is not found, it informs the user.

int main(void) {
    // The main function serves as the entry point of the program. It displays a menu to the user and processes their choices in a loop until they choose to exit.

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
    // the do-while loop continues to display the menu and process user choices until the user selects option 5 to exit the program.

    return 0;
}