#include <stdio.h>
#include <string.h>
#include "budget.h"
#include "validation.h"

// Scoped globally so reports.c can access budget records directly
char  deptName[MAX_DEPTS][NAME_LEN];
float allocated[MAX_DEPTS];
float expenditure[MAX_DEPTS];
int   deptCount = 0;

void addDepartment(void) {
    if (deptCount >= MAX_DEPTS) {
        printf("Department list is full.\n");
        return;
    }
    readNonEmptyString("Enter department name: ", deptName[deptCount], NAME_LEN);
    allocated[deptCount] = readNonNegativeFloat("Enter allocated budget (N$): ");
    expenditure[deptCount] = 0.0f;
    
    printf("Department added: %s, allocated N$%.2f\n", deptName[deptCount], allocated[deptCount]);
    deptCount++;
}

void enterExpenditure(void) {
    char name[NAME_LEN];
    int found = -1;

    if (deptCount == 0) {
        printf("No departments registered yet.\n");
        return;
    }
    readNonEmptyString("Enter department name: ", name, NAME_LEN);

    for (int i = 0; i < deptCount; i++) {
        if (strcmp(deptName[i], name) == 0) {
            found = i;
            break;
        }
    }
    if (found == -1) {
        printf("Department not found.\n");
        return;
    }
    float amount = readNonNegativeFloat("Enter expenditure amount (N$): ");
    expenditure[found] += amount;
    printf("Expenditure recorded: N$%.2f for %s\n", amount, deptName[found]);
}

float remaining(int i) {
    return allocated[i] - expenditure[i];
}

int isWithinBudget(int i) {
    return (remaining(i) >= 0) ? 1 : 0;
}

void displayBudgets(void) {
    if (deptCount == 0) {
        printf("No departments have been entered yet.\n");
        return;
    }
    for (int i = 0; i < deptCount; i++) {
        printf("\nDepartment: %s\n", deptName[i]);
        printf("Allocated Budget: N$%.2f\n", allocated[i]);
        printf("Expenditure: N$%.2f\n", expenditure[i]);
        printf("Remaining Budget: N$%.2f\n", remaining(i));
        printf("Status: %s\n", isWithinBudget(i) ? "WITHIN BUDGET" : "OVER BUDGET");
    }
}

void listOverBudget(void) {
    int count = 0;
    printf("\nDepartments that have exceeded their budget:\n");
    for (int i = 0; i < deptCount; i++) {
        if (!isWithinBudget(i)) {
            printf("- %s (over by N$%.2f)\n", deptName[i], -remaining(i));
            count++;
        }
    }
    if (count == 0) printf("None. All departments are within budget.\n");
}

void budgetMenu(void) {
    int choice;
    do {
        printf("\n===== BUDGET MANAGEMENT =====\n");
        printf("1. Add department budget\n");
        printf("2. Enter expenditure\n");
        printf("3. Display budget information\n");
        printf("4. List departments over budget\n");
        printf("5. Back to Main Menu\n");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) choice = -1;
        clearInputBuffer();

        switch (choice) {
            case 1: addDepartment(); break;
            case 2: enterExpenditure(); break;
            case 3: displayBudgets(); break;
            case 4: listOverBudget(); break;
            case 5: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 5);
}
