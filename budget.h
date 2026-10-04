#ifndef BUDGET_H
#define BUDGET_H

#define MAX_DEPTS 25
#define NAME_LEN 45

void addDepartment(void);
void enterExpenditure(void);
float remaining(int i);
int isWithinBudget(int i);
void displayBudgets(void);
void listOverBudget(void);
void budgetMenu(void);

#endif