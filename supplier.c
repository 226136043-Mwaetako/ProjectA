#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "supplier.h"

#define MAX_SUP 50
#define NAME_LEN 50
#define EMAIL_LEN 50
#define PHONE_LEN 20
#define TOWN_LEN 30


static int supID[MAX_SUP];
static char supName[MAX_SUP][NAME_LEN];
static char supEmail[MAX_SUP][EMAIL_LEN];
static char supPhone[MAX_SUP][PHONE_LEN];
static char supTown[MAX_SUP][TOWN_LEN];
static int supCount = 0;


static void readLine(char text[], int size);
static int readInt(void);
static int isBlank(char text[]);
static int isValidEmail(char email[]);
static int isValidPhone(char phone[]);
static int findSupplierByID(int id);
static int emailExists(char email[]);
static int containsIgnoreCase(char text[], char part[]);
static void showSupplier(int i);


static void readLine(char text[], int size)
{
    if (fgets(text, size, stdin) == NULL)
    {
        text[0] = '\0';
        return;
    }

    int len = strlen(text);

    if (len > 0 && text[len - 1] == '\n')
    {
        text[len - 1] = '\0';
    }
    else
    {
        
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
    }
}


static int readInt(void)
{
    char line[30];
    int value;

    readLine(line, sizeof(line));

    if (sscanf(line, "%d", &value) != 1)
    {
        return -1;
    }
    return value;
}


static int isBlank(char text[])
{
    for (int i = 0; i < (int)strlen(text); i++)
    {
        if (!isspace((unsigned char)text[i]))
        {
            return 0;
        }
    }
    return 1;
}


static int isValidEmail(char email[])
{
    char *at = strchr(email, '@');

    if (at == NULL || at == email)
    {
        return 0;
    }
    if (strchr(at, '.') == NULL)
    {
        return 0;
    }
    if (strchr(email, ' ') != NULL)
    {
        return 0;
    }
    if (email[strlen(email) - 1] == '.')
    {
        return 0;
    }
    return 1;
}


static int isValidPhone(char phone[])
{
    int len = strlen(phone);
    int start = 0;

    if (len > 0 && phone[0] == '+')
    {
        start = 1;
    }

    if (len - start < 7 || len - start > 15)
    {
        return 0;
    }

    for (int i = start; i < len; i++)
    {
        if (!isdigit((unsigned char)phone[i]))
        {
            return 0;
        }
    }
    return 1;
}


static int findSupplierByID(int id)
{
    for (int i = 0; i < supCount; i++)
    {
        if (supID[i] == id)
        {
            return i;
        }
    }
    return -1;
}


static int emailExists(char email[])
{
    for (int i = 0; i < supCount; i++)
    {
        if (strcmp(supEmail[i], email) == 0)
        {
            return 1;
        }
    }
    return 0;
}


static int containsIgnoreCase(char text[], char part[])
{
    char a[100];
    char b[100];

    strncpy(a, text, sizeof(a) - 1);
    a[sizeof(a) - 1] = '\0';
    strncpy(b, part, sizeof(b) - 1);
    b[sizeof(b) - 1] = '\0';

    for (int i = 0; a[i] != '\0'; i++)
    {
        a[i] = tolower((unsigned char)a[i]);
    }
    for (int i = 0; b[i] != '\0'; i++)
    {
        b[i] = tolower((unsigned char)b[i]);
    }

    return strstr(a, b) != NULL;
}


static void showSupplier(int i)
{
    printf("Supplier ID : %d\n", supID[i]);
    printf("Name : %s\n", supName[i]);
    printf("Email : %s\n", supEmail[i]);
    printf("Telephone : %s\n", supPhone[i]);
    printf("Town : %s\n", supTown[i]);
}



int GetSupplierCount(void)
{
    return supCount;
}

void AddSupplier(void)
{
    int id;
    char name[NAME_LEN];
    char email[EMAIL_LEN];
    char phone[PHONE_LEN];
    char town[TOWN_LEN];

    if (supCount >= MAX_SUP)
    {
        printf("Supplier list is full.\n");
        return;
    }


    do
    {
        printf("Enter Supplier ID: ");
        id = readInt();

        if (id <= 0)
        {
            printf("Invalid ID. Please enter a positive number.\n");
        }
        else if (findSupplierByID(id) != -1)
        {
            printf("That ID already exists.\n");
            id = -1;
        }
    } while (id <= 0);

    
    do
    {
        printf("Enter Supplier Name: ");
        readLine(name, sizeof(name));

        if (isBlank(name))
        {
            printf("Name cannot be empty.\n");
        }
    } while (isBlank(name));

    
    do
    {
        printf("Enter Supplier Email: ");
        readLine(email, sizeof(email));

        if (!isValidEmail(email))
        {
            printf("Invalid email. Example: name@company.com\n");
            email[0] = '\0';
        }
        else if (emailExists(email))
        {
            printf("That email is already registered.\n");
            email[0] = '\0';
        }
    } while (email[0] == '\0');

    
    do
    {
        printf("Enter Telephone Number: ");
        readLine(phone, sizeof(phone));

        if (!isValidPhone(phone))
        {
            printf("Invalid number. Use 7 to 15 digits only.\n");
        }
    } while (!isValidPhone(phone));

    
    do
    {
        printf("Enter Town/Location: ");
        readLine(town, sizeof(town));

        if (isBlank(town))
        {
            printf("Town cannot be empty.\n");
        }
    } while (isBlank(town));

    
    supID[supCount] = id;
    strcpy(supName[supCount], name);
    strcpy(supEmail[supCount], email);
    strcpy(supPhone[supCount], phone);
    strcpy(supTown[supCount], town);
    supCount++;

    printf("Supplier added successfully.\n");
}

void DisplaySuppliers(void)
{
    if (supCount == 0)
    {
        printf("\nNo suppliers registered yet.\n");
        return;
    }

    printf("\n=============== SUPPLIER LIST ===============\n");
    for (int i = 0; i < supCount; i++)
    {
        printf("\nSupplier %d of %d\n", i + 1, supCount);
        showSupplier(i);
    }
    printf("\n=============================================\n");
    printf("Total suppliers: %d\n", supCount);
}

void SearchSupplier(void)
{
    int option;
    int found = 0;

    if (supCount == 0)
    {
        printf("\nNo suppliers registered yet.\n");
        return;
    }

    printf("\nSearch by:\n");
    printf("1. Supplier ID\n");
    printf("2. Supplier Name\n");
    printf("3. Town/Location\n");
    printf("Enter your choice: ");
    option = readInt();

    if (option == 1)
    {
        int id;
        printf("Enter Supplier ID: ");
        id = readInt();

        int index = findSupplierByID(id);
        if (index != -1)
        {
            printf("\nSupplier found:\n");
            showSupplier(index);
            found = 1;
        }
    }
    else if (option == 2)
    {
        char name[NAME_LEN];
        printf("Enter Supplier Name (or part of it): ");
        readLine(name, sizeof(name));

        if (isBlank(name))
        {
            printf("Search text cannot be empty.\n");
            return;
        }

        for (int i = 0; i < supCount; i++)
        {
            if (containsIgnoreCase(supName[i], name))
            {
                printf("\nSupplier found:\n");
                showSupplier(i);
                found = 1;
            }
        }
    }
    else if (option == 3)
    {
        char town[TOWN_LEN];
        printf("Enter Town/Location: ");
        readLine(town, sizeof(town));

        if (isBlank(town))
        {
            printf("Search text cannot be empty.\n");
            return;
        }

        for (int i = 0; i < supCount; i++)
        {
            if (containsIgnoreCase(supTown[i], town))
            {
                printf("\nSupplier found:\n");
                showSupplier(i);
                found = 1;
            }
        }
    }
    else
    {
        printf("Invalid choice.\n");
        return;
    }

    if (!found)
    {
        printf("No matching supplier found.\n");
    }
}

void SupplierMenu(void)
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf(" SUPPLIER MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add Supplier\n");
        printf("2. Display Suppliers\n");
        printf("3. Search Supplier\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");
        choice = readInt();

        switch (choice)
        {
            case 1:
                AddSupplier();
                break;
            case 2:
                DisplaySuppliers();
                break;
            case 3:
                SearchSupplier();
                break;
            case 4:
                printf("Returning to main menu.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}