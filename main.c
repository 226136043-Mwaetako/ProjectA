#include <stdio.h>
#include <string.h>

#define MAX_ASSETS 100
#define MAX_EMPLOYEES 100

struct Asset {
    int assetID;
    char assetName[50];
    char assetType[30];
    float purchaseValue;
    char department[50];
    char condition[30];
};

struct Employee {
    int employeeID;
    char name[50];       
    char department[50];  
    float basicSalary;
    float housingAllowance;
    float transportAllowance;
    float grossSalary;
};

struct Asset assets[MAX_ASSETS];
int assetCount = 0;

struct Employee employees[MAX_EMPLOYEES];
int employeeCount = 0;

void addAsset() {
    if (assetCount >= MAX_ASSETS) {
        printf("Asset register is full.\n");
        return;
    }
    printf("\n--- Add Asset ---\n");
    printf("Enter Asset ID: ");
    scanf("%d", &assets[assetCount].assetID);
    printf("Enter Asset Name: ");
    scanf(" %[^\n]", assets[assetCount].assetName);
    printf("Enter Asset Type: ");
    scanf(" %[^\n]", assets[assetCount].assetType);
    printf("Enter Purchase Value: N$");
    scanf("%f", &assets[assetCount].purchaseValue);
    printf("Enter Department: ");
    scanf(" %[^\n]", assets[assetCount].department);
    printf("Enter Condition: ");
    scanf(" %[^\n]", assets[assetCount].condition);
    assetCount++;
    printf("\nAsset added successfully!\n");
}

void displayAssets() {
    int i;
    if (assetCount == 0) {
        printf("\nNo assets registered.\n");
        return;
    }
    printf("\n========== ASSET REGISTER ==========\n");
    for (i = 0; i < assetCount; i++) {
        printf("\nAsset ID: %d\n", assets[i].assetID);
        printf("Asset Name: %s\n", assets[i].assetName);
        printf("Asset Type: %s\n", assets[i].assetType);
        printf("Purchase Value: N$%.2f\n", assets[i].purchaseValue);
        printf("Department: %s\n", assets[i].department);
        printf("Condition: %s\n", assets[i].condition);
    }
}

void searchAsset() {
    int id, i, found = 0;
    printf("\nEnter Asset ID to search: ");
    scanf("%d", &id);
    for (i = 0; i < assetCount; i++) {
        if (assets[i].assetID == id) {
            printf("\n--- Asset Found ---\n");
            printf("Asset ID: %d\n", assets[i].assetID);
            printf("Asset Name: %s\n", assets[i].assetName);
            printf("Asset Type: %s\n", assets[i].assetType);
            printf("Purchase Value: N$%.2f\n", assets[i].purchaseValue);
            printf("Department: %s\n", assets[i].department);
            printf("Condition: %s\n", assets[i].condition);
            found = 1;
            break;
        }
    }
    if (!found) printf("\nAsset not found.\n");
}

void assetManagement() {
    int choice;
    do {
        printf("\n=================================\n");
        printf("       ASSET MANAGEMENT\n");
        printf("=================================\n");
        printf("1. Add Asset\n");
        printf("2. Display Assets\n");
        printf("3. Search Asset\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addAsset(); break;
            case 2: displayAssets(); break;
            case 3: searchAsset(); break;
            case 4: printf("Returning to Main Menu...\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}

void addEmployee() {
    if (employeeCount >= MAX_EMPLOYEES) {
        printf("Employee register is full.\n");
        return;
    }

    printf("\n--- Add Employee ---\n");
    printf("Enter Employee ID: ");
    scanf("%d", &employees[employeeCount].employeeID);

    
    int i;
    for (i = 0; i < employeeCount; i++) {
        if (employees[i].employeeID == employees[employeeCount].employeeID) {
            printf("Error: Employee ID %d already exists!\n", employees[employeeCount].employeeID);
            return;
        }
    }

    printf("Enter Name: ");
    scanf(" %[^\n]", employees[employeeCount].name);

    printf("Enter Department: ");
    scanf(" %[^\n]", employees[employeeCount].department);

    printf("Enter Basic Salary: N$");
    scanf("%f", &employees[employeeCount].basicSalary);
    if (employees[employeeCount].basicSalary < 0) {
        printf("Error: Basic salary cannot be negative!\n");
        return;
    }

    printf("Enter Housing Allowance: N$");
    scanf("%f", &employees[employeeCount].housingAllowance);
    if (employees[employeeCount].housingAllowance < 0) {
        printf("Error: Allowance cannot be negative!\n");
        return;
    }

    printf("Enter Transport Allowance: N$");
    scanf("%f", &employees[employeeCount].transportAllowance);
    if (employees[employeeCount].transportAllowance < 0) {
        printf("Error: Allowance cannot be negative!\n");
        return;
    }


    employees[employeeCount].grossSalary = employees[employeeCount].basicSalary + 
                                           employees[employeeCount].housingAllowance + 
                                           employees[employeeCount].transportAllowance;

    employeeCount++;
    printf("\nEmployee added successfully!\n");
}

void displayEmployees() {
    int i;
    if (employeeCount == 0) {
        printf("\nNo employees registered.\n");
        return;
    }
    printf("\n========== EMPLOYEE REGISTER ==========\n");
    for (i = 0; i < employeeCount; i++) {
        printf("\nEmployee ID: %d\n", employees[i].employeeID);
        printf("Name: %s\n", employees[i].name);
        printf("Department: %s\n", employees[i].department);
        printf("Basic Salary: N$%.2f\n", employees[i].basicSalary);
        printf("Housing Allowance: N$%.2f\n", employees[i].housingAllowance);
        printf("Transport Allowance: N$%.2f\n", employees[i].transportAllowance);
        printf("Gross Total Salary: N$%.2f\n", employees[i].grossSalary);
        printf("---------------------------------------\n");
    }
}

void searchEmployee() {
    int id, i, found = 0;
    if (employeeCount == 0) {
        printf("\nNo records available to search.\n");
        return;
    }
    printf("\nEnter Employee ID to search: ");
    scanf("%d", &id);
    for (i = 0; i < employeeCount; i++) {
        if (employees[i].employeeID == id) {
            printf("\n--- Employee Found ---\n");
            printf("Employee ID: %d\n", employees[i].employeeID);
            printf("Name: %s\n", employees[i].name);
            printf("Department: %s\n", employees[i].department);
            printf("Basic Salary: N$%.2f\n", employees[i].basicSalary);
            printf("Housing Allowance: N$%.2f\n", employees[i].housingAllowance);
            printf("Transport Allowance: N$%.2f\n", employees[i].transportAllowance);
            printf("Gross Total Salary: N$%.2f\n", employees[i].grossSalary);
            found = 1;
            break;
        }
    }
    if (!found) printf("\nEmployee record not found.\n");
}

void calculateSalaryInfo() {
    if (employeeCount == 0) {
        printf("\nNo employee metrics to calculate.\n");
        return;
    }
    float totalPayroll = 0;
    int i;
    printf("\n--- Payroll Breakdown ---\n");
    for (i = 0; i < employeeCount; i++) {
        printf("%s (ID: %d) -> Gross Salary: N$%.2f\n", employees[i].name, employees[i].employeeID, employees[i].grossSalary);
        totalPayroll += employees[i].grossSalary;
    }
    printf("\nTotal Monthly Payroll Expenditure: N$%.2f\n", totalPayroll);
}

void employeeManagement() {
    int choice;
    do {
        printf("\n=================================\n");
        printf("       EMPLOYEE MANAGEMENT\n");
        printf("=================================\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Calculate Salary Information\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: calculateSalaryInfo(); break;
            case 5: printf("Returning to Main Menu...\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
}


int main() {
    int choice;
    do {
        printf("\n=========================================\n");
        printf("  MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
        printf("=========================================\n");
        printf("1. Employee Management\n");
        printf("2. Budget Management (Stub)\n");
        printf("3. Supplier Management (Stub)\n");
        printf("4. Asset Management\n");
        printf("5. Reports (Stub)\n");
        printf("6. Exit\n");
        printf("=========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

    
        switch (choice) {
            case 1:
                employeeManagement();
                break;
            case 2:
                printf("\nBudget Management module placeholder.\n");
                break;
            case 3:
                printf("\nSupplier Management module placeholder.\n");
                break;
            case 4:
                assetManagement(); 
                break;
            case 5:
                printf("\nReports module placeholder.\n");
                break;
            case 6:
                printf("\nExiting Municipal Financial Management System. Goodbye!\n");
                break;
            default:
                printf("\nInvalid choice! Please select a valid option from the menu.\n");
        }
    } while (choice != 6);

    return 0;
}
