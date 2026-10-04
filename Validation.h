#ifndef VALIDATION_H
#define VALIDATION_H

void  clearInputBuffer(void);
float readNonNegativeFloat(const char prompt[]);
int   readIntegerRange(const char prompt[], int min, int max);

// Expose both names so different student files both compile perfectly
void  readValidatedString(const char prompt[], char *output, int maxLength);
void  readNonEmptyString(const char prompt[], char *output, int maxLength);

#endif
