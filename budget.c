#include <stdio.h>
#include <string.h>
#include "budget.h"

char  deptName[MAX_DEPTS][NAME_LEN];
float allocated[MAX_DEPTS];
float expenditure[MAX_DEPTS];
int   deptCount = 0;

void addDepartment(void) {
    char name[NAME_LEN];
    float budget;

    if (deptCount >= MAX_DEPTS) {
        printf("Department list is full.\n");
        return;
    }
    printf("Enter department name (one word): ");
    scanf("%49s", name);
    printf("Enter allocated budget (N$): ");
    scanf("%f", &budget);

    if (budget < 0) {
        printf("Budget cannot be negative.\n");
        return;
    }
    strcpy(deptName[deptCount], name);
    allocated[deptCount] = budget;
    expenditure[deptCount] = 0;
    deptCount++;
    printf("Department added: %s, allocated N$%.2f\n", name, budget);
}
void enterExpenditure(void) {
    char name[NAME_LEN];
    float amount;
    int i, found = -1;

    printf("Enter department name: ");
    scanf("%49s", name);

    for (i = 0; i < deptCount; i++) {
        if (strcmp(deptName[i], name) == 0) {
            found = i;
            break;
        }
    }
    if (found == -1) {
        printf("Department not found.\n");
        return;
    }
    printf("Enter expenditure amount (N$): ");
    scanf("%f", &amount);
    if (amount <= 0) {
        printf("Amount must be positive.\n");
        return;
    }
    expenditure[found] += amount;
    printf("Expenditure recorded: N$%.2f for %s\n", amount, deptName[found]);
}
float remaining(int i) {
    return allocated[i] - expenditure[i];
}
int isWithinBudget(int i) {
    if (remaining(i) >= 0) {
        return 1;
    }
    return 0;
}
void displayBudgets(void) {
    int i;

    if (deptCount == 0) {
        printf("No departments have been entered yet.\n");
        return ;
    }
    for (i = 0; i < deptCount; i++) {
        printf("\nDepartment: %s\n", deptName[i]);
        printf("Allocated Budget: N$%.2f\n", allocated[i]);
        printf("Expenditure: N$%.2f\n", expenditure[i]);
        printf("Remaining Budget: N$%.2f\n", remaining(i));
        if (isWithinBudget(i)) {
            printf("Status: WITHIN BUDGET\n");
        } else {
            printf("Status: OVER BUDGET\n");
        }
    }
}
void listOverBudget(void) {
    int i, count = 0;

    printf("\nDepartments that have exceeded their budget:\n");
    for (i = 0; i < deptCount; i++) {
        if (!isWithinBudget(i)) {
            printf("- %s (over by N$%.2f)\n", deptName[i], -remaining(i));
            count++;
        }
    }
    if (count == 0) {
        printf("None. All departments are within budget.\n");
    }
}
void budgetMenu(void) {
    int choice;

    do {
        printf("\n===== BUDGET MANAGEMENT =====\n");
        printf("1. Add department budget\n");
        printf("2. Enter expenditure\n");
        printf("3. Display budget information\n");
        printf("4. List departments over budget\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addDepartment(); break;
            case 2: enterExpenditure(); break;
            case 3: displayBudgets(); break;
            case 4: listOverBudget(); break;
            case 0: printf("Goodbye.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);

}
