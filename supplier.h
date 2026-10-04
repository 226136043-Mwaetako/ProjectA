#ifndef SUPPLIER_H
#define SUPPLIER_H

#define MAX_SUP 50
#define SUP_NAME_LEN 50  // Renamed to fix the macro definition overlap warning!
#define EMAIL_LEN 50
#define PHONE_LEN 20
#define TOWN_LEN 30

extern int  supID[MAX_SUP];
extern char supName[MAX_SUP][SUP_NAME_LEN];
extern char supEmail[MAX_SUP][EMAIL_LEN];
extern char supPhone[MAX_SUP][PHONE_LEN];
extern char supTown[MAX_SUP][TOWN_LEN];
extern int  supCount;

void AddSupplier(void);
void DisplaySuppliers(void);
void SearchSupplier(void);
void SupplierMenu(void);
int  GetSupplierCount(void);

#endif