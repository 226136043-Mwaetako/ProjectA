#include <stdio.h>
#include <string.h>
#include "validation.h"

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

float readNonNegativeFloat(const char prompt[]) {
    float value = 0;
    int ok;
    do {
        printf("%s", prompt);
        ok = scanf("%f", &value);
        clearInputBuffer();

        if (ok != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            ok = 0;
        } else if (value < 0) {
            printf("Value cannot be negative.\n");
            ok = 0;
        }
    } while (!ok);
    return value;
}

int readIntegerRange(const char prompt[], int min, int max) {
    int value;
    int ok;
    do {
        printf("%s", prompt);
        ok = scanf("%d", &value);
        clearInputBuffer();

        if (ok != 1 || value < min || value > max) {
            printf("Invalid selection! Please enter a number between %d and %d.\n", min, max);
            ok = 0;
        }
    } while (!ok);
    return value;
}

// Implement both to do the exact same safe string reading
void readValidatedString(const char prompt[], char *output, int maxLength) {
    do {
        printf("%s", prompt);
        if (fgets(output, maxLength, stdin) == NULL) {
            output[0] = '\0';
        }
        output[strcspn(output, "\n")] = '\0'; 

        if (strlen(output) == 0) {
            printf("Input cannot be empty. Please try again.\n");
        }
    } while (strlen(output) == 0);
}

void readNonEmptyString(const char prompt[], char *output, int maxLength) {
    readValidatedString(prompt, output, maxLength);
}
