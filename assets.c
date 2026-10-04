#include <stdio.h>
#include <string.h>
#include "assets.h"
#include "validation.h"

Asset assets[MAX_ASSETS];
int assetCount = 0;

static int findAssetByID(const char id[]) {
    for (int i = 0; i < assetCount; i++) {
        if (strcmp(assets[i].assetID, id) == 0) return i;
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
        readNonEmptyString("Enter Asset ID: ", a->assetID, sizeof(a->assetID));
        if (findAssetByID(a->assetID) != -1) printf("An asset with that ID already exists.\n");
        else break;
    }

    readNonEmptyString("Enter Asset Name: ", a->assetName, sizeof(a->assetName));
    readNonEmptyString("Enter Asset Type: ", a->assetType, sizeof(a->assetType));
    a->purchaseValue = (double)readNonNegativeFloat("Enter Purchase Value (N$): ");
    readNonEmptyString("Enter Department: ", a->department, sizeof(a->department));

    int choice = 0;
    do {
        printf("Condition:\n1. Good\n2. Fair\n3. Poor\nChoose (1-3): ");
        if (scanf("%d", &choice) != 1) choice = 0;
        clearInputBuffer();

        if (choice == 1) strcpy(a->condition, "Good");
        else if (choice == 2) strcpy(a->condition, "Fair");
        else if (choice == 3) strcpy(a->condition, "Poor");
        else printf("Invalid choice.\n");
    } while (choice < 1 || choice > 3);

    assetCount++;
    printf("Asset added successfully.\n");
}

void displayAssets(void) {
    if (assetCount == 0) { printf("\nNo assets registered.\n"); return; }
    printf("\nAsset Register (%d assets)\n", assetCount);
    for (int i = 0; i < assetCount; i++) {
        printf("\n=============== Asset %d ===============\n", i + 1);
        printAsset(&assets[i]);
    }
}

void searchAsset(void) {
    char term[80]; int found = 0;
    readNonEmptyString("Enter Asset ID or Name to search: ", term, sizeof(term));
    for (int i = 0; i < assetCount; i++) {
        if (strcmp(assets[i].assetID, term) == 0 || strcmp(assets[i].assetName, term) == 0) {
            printf("\nAsset Found:\n"); printAsset(&assets[i]); found = 1;
        }
    }
    if (!found) printf("No asset found matching \"%s\".\n", term);
}

void assetMenu(void) {
    int choice;
    do {
        printf("\n===== ASSET MANAGEMENT =====\n");
        printf("1. Add Asset\n");
        printf("2. Display Assets\n");
        printf("3. Search Asset\n");
        printf("4. Back to Main Menu\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) choice = -1;
        clearInputBuffer();
        switch (choice) {
            case 1: addAsset(); break;
            case 2: displayAssets(); break;
            case 3: searchAsset(); break;
            case 4: break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);
}