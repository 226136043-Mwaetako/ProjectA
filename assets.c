#include <stdio.h>
#include <string.h>
#include "assets.h"


static Asset assets[MAX_ASSETS];
static int assetCount = 0;


static void clearBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}


static void readText(const char prompt[], char dest[], int size) {
    printf("%s", prompt);
    if (fgets(dest, size, stdin) == NULL) {
        dest[0] = '\0';
        return;
    }
    char *nl = strchr(dest, '\n');
    if (nl != NULL) {
        *nl = '\0';
    } else {
        
    }
}


static double readNonNegativeDouble(const char prompt[]) {
    double value = 0;
    int ok;

    do {
        printf("%s", prompt);
        ok = scanf(" %lf", &value);
        clearBuffer();

        if (ok != 1) {
            printf("Invalid input. Please enter a number.\n");
        } else if (value < 0) {
            printf("Value cannot be negative.\n");
            ok = 0;
        }
    } while (ok != 1);

    return value;
}


static int findAssetByID(const char id[]) {
    for (int i = 0; i < assetCount; i++) {
        if (strcmp(assets[i].assetID, id) == 0) {
            return i;
        }
    }
    return -1;
}

static void printAsset(const Asset *a) {
    printf("Asset ID: %s\n", a->assetID);
    printf("Asset Name: %s\n", a->assetName);
    printf("Asset Type: %s\n", a->assetType);
    printf("Purchase Value: N$%.2f\n", a->purchaseValue);
    printf("Department: %s\n", a->department);
    printf("Condition: %s\n", a->condition);
}

void addAsset(void) {
    if (assetCount >= MAX_ASSETS) {
        printf("Asset register is full.\n");
        return;
    }

    Asset *a = &assets[assetCount];

    
    while (1) {
        readText("Enter Asset ID: ", a->assetID, sizeof(a->assetID));
        if (strlen(a->assetID) == 0) {
            printf("Asset ID cannot be empty.\n");
        } else if (findAssetByID(a->assetID) != -1) {
            printf("An asset with that ID already exists.\n");
        } else {
            break;
        }
    }

    do {
        readText("Enter Asset Name: ", a->assetName, sizeof(a->assetName));
        if (strlen(a->assetName) == 0) {
            printf("Asset name cannot be empty.\n");
        }
    } while (strlen(a->assetName) == 0);

    do {
        readText("Enter Asset Type (e.g. Vehicle, Computer): ",
                 a->assetType, sizeof(a->assetType));
        if (strlen(a->assetType) == 0) {
            printf("Asset type cannot be empty.\n");
        }
    } while (strlen(a->assetType) == 0);

    a->purchaseValue = readNonNegativeDouble("Enter Purchase Value (N$): ");

    do {
        readText("Enter Department: ", a->department, sizeof(a->department));
        if (strlen(a->department) == 0) {
            printf("Department cannot be empty.\n");
        }
    } while (strlen(a->department) == 0);

    
    int choice = 0;
    do {
        printf("Condition:\n1. Good\n2. Fair\n3. Poor\nChoose (1-3): ");
        if (scanf("%d", &choice) != 1) {
            choice = 0;
        }
        clearBuffer();

        if (choice == 1) {
            strcpy(a->condition, "Good");
        } else if (choice == 2) {
            strcpy(a->condition, "Fair");
        } else if (choice == 3) {
            strcpy(a->condition, "Poor");
        } else {
            printf("Invalid choice. Enter 1, 2 or 3.\n");
        }
    } while (choice < 1 || choice > 3);

    assetCount++;
    printf("Asset added successfully.\n");
}

void displayAssets(void) {
    if (assetCount == 0) {
        printf("\nNo assets registered.\n");
        return;
    }

    printf("\nAsset Register (%d assets)\n", assetCount);
    for (int i = 0; i < assetCount; i++) {
        printf("\n=============== Asset %d ===============\n", i + 1);
        printAsset(&assets[i]);
    }
    printf("\n========================================\n");
}

void searchAsset(void) {
    char term[80];
    int found = 0;

    readText("Enter Asset ID or Name to search: ", term, sizeof(term));

    if (strlen(term) == 0) {
        printf("Search term cannot be empty.\n");
        return;
    }

    for (int i = 0; i < assetCount; i++) {
        if (strcmp(assets[i].assetID, term) == 0 ||
            strcmp(assets[i].assetName, term) == 0) {
            printf("\nAsset Found:\n");
            printAsset(&assets[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("No asset found matching \"%s\".\n", term);
    }
}

void assetMenu(void) {
    int choice;

    do {
        printf("\n===== ASSET MANAGEMENT =====\n");
        printf("1. Add Asset\n");
        printf("2. Display Assets\n");
        printf("3. Search Asset\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            choice = -1;
        }
        clearBuffer();

        switch (choice) {
            case 1:
                addAsset();
                break;
            case 2:
                displayAssets();
                break;
            case 3:
                searchAsset();
                break;
            case 4:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}
