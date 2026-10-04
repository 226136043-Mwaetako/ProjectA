#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "supplier.h"
#include "validation.h"

int  supID[MAX_SUP];
char supName[MAX_SUP][SUP_NAME_LEN]; // Updated to match header
char supEmail[MAX_SUP][EMAIL_LEN];
char supPhone[MAX_SUP][PHONE_LEN];
char supTown[MAX_SUP][TOWN_LEN];
int  supCount = 0;

static int readInt(void) {
    int val;
    if (scanf("%d", &val) != 1) {
        val = -1;
    }
    clearInputBuffer();
    return val;
}

static int isBlank(char text[]) {
    for (int i = 0; i < (int)strlen(text); i++) {
        if (!isspace((unsigned char)text[i])) return 0;
    }
    return 1;
}

static int isValidEmail(char email[]) {
    char *at = strchr(email, '@');
    if (at == NULL || at == email) return 0;
    if (strchr(at, '.') == NULL) return 0;
    if (strchr(email, ' ') != NULL) return 0;
    return 1;
}

static int isValidPhone(char phone[]) {
    int len = strlen(phone);
    if (len < 7 || len > 15) return 0;
    for (int i = 0; i < len; i++) {
        if (!isdigit((unsigned char)phone[i]) && phone[i] != '+') return 0;
    }
    return 1;
}

static int findSupplierByID(int id) {
    for (int i = 0; i < supCount; i++) {
        if (supID[i] == id) return i;
    }
    return -1;
}

static int emailExists(char email[]) {
    for (int i = 0; i < supCount; i++) {
        if (strcmp(supEmail[i], email) == 0) return 1;
    }
    return 0;
}

static int containsIgnoreCase(char text[], char part[]) {
    char a[100], b[100];
    strncpy(a, text, sizeof(a)-1); a[sizeof(a)-1] = '\0';
    strncpy(b, part, sizeof(b)-1); b[sizeof(b)-1] = '\0';
    for(int i=0; a[i]; i++) a[i] = tolower((unsigned char)a[i]);
    for(int i=0; b[i]; i++) b[i] = tolower((unsigned char)b[i]);
    return strstr(a, b) != NULL;
}

static void showSupplier(int i) {
    printf("Supplier ID : %d\n", supID[i]);
    printf("Name        : %s\n", supName[i]);
    printf("Email       : %s\n", supEmail[i]);
    printf("Telephone   : %s\n", supPhone[i]);
    printf("Town        : %s\n", supTown[i]);
}

int GetSupplierCount(void) { return supCount; }

void AddSupplier(void) {
    if (supCount >= MAX_SUP) {
        printf("Supplier list is full.\n");
        return;
    }
    int id;
    do {
        printf("Enter Supplier ID: ");
        id = readInt();
        if (id <= 0) printf("Invalid ID. Use a positive number.\n");
        else if (findSupplierByID(id) != -1) { printf("That ID already exists.\n"); id = -1; }
    } while (id <= 0);

    readNonEmptyString("Enter Supplier Name: ", supName[supCount], SUP_NAME_LEN);
    
    do {
        readNonEmptyString("Enter Supplier Email: ", supEmail[supCount], EMAIL_LEN);
        if (!isValidEmail(supEmail[supCount])) { printf("Invalid email structure.\n"); supEmail[supCount][0] = '\0'; }
        else if (emailExists(supEmail[supCount])) { printf("Email already exists.\n"); supEmail[supCount][0] = '\0'; }
    } while (supEmail[supCount][0] == '\0');

    do {
        readNonEmptyString("Enter Telephone Number: ", supPhone[supCount], PHONE_LEN);
        if (!isValidPhone(supPhone[supCount])) printf("Invalid phone structure.\n");
    } while (!isValidPhone(supPhone[supCount]));

    readNonEmptyString("Enter Town/Location: ", supTown[supCount], TOWN_LEN);

    supID[supCount] = id;
    supCount++;
    printf("Supplier added successfully.\n");
}

void DisplaySuppliers(void) {
    if (supCount == 0) { printf("\nNo suppliers registered yet.\n"); return; }
    printf("\n=============== SUPPLIER LIST ===============\n");
    for (int i = 0; i < supCount; i++) {
        printf("\nSupplier %d of %d\n", i + 1, supCount);
        showSupplier(i);
    }
}

void SearchSupplier(void) {
    if (supCount == 0) { printf("\nNo suppliers registered yet.\n"); return; }
    int option, found = 0;
    printf("\nSearch by:\n1. ID\n2. Name\n3. Town\nEnter Choice: ");
    option = readInt();

    if (option == 1) {
        printf("Enter ID: ");
        int idx = findSupplierByID(readInt());
        if (idx != -1) { showSupplier(idx); found = 1; }
    } else if (option == 2) {
        char q[SUP_NAME_LEN]; 
        // Fixed: changed the size parameter here from NAME_LEN to SUP_NAME_LEN
        readNonEmptyString("Enter search string: ", q, SUP_NAME_LEN);
        for (int i = 0; i < supCount; i++) if (containsIgnoreCase(supName[i], q)) { showSupplier(i); found = 1; }
    } else if (option == 3) {
        char q[TOWN_LEN]; readNonEmptyString("Enter town: ", q, TOWN_LEN);
        for (int i = 0; i < supCount; i++) if (containsIgnoreCase(supTown[i], q)) { showSupplier(i); found = 1; }
    }
    if (!found) printf("No matched records found.\n");
}

void SupplierMenu(void) {
    int choice;
    do {
        printf("\n===== SUPPLIER MANAGEMENT =====\n");
        printf("1. Add Supplier\n");
        printf("2. Display Suppliers\n");
        printf("3. Search Supplier\n");
        printf("4. Back to Main Menu\n");
        printf("Enter choice: ");
        choice = readInt();
        switch (choice) {
            case 1: AddSupplier(); break;
            case 2: DisplaySuppliers(); break;
            case 3: SearchSupplier(); break;
            case 4: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 4);
}
