#ifndef EmployeeManagement_h
#define EmployeeManagement_h

#define max_Employees 50

extern char EmployeeName[max_Employees][50];
extern char EmployeeID[max_Employees][10];
extern char Department[max_Employees][50];

extern float BasicSalary[max_Employees];
extern float HousingAllowance[max_Employees];
extern float TransportAllowance[max_Employees];

extern char PhoneNumber[max_Employees][15];
extern char EmployeeEmail[max_Employees][50];
extern int NumberOfEmployees;

void clearInputBuffer(void);
float readNonNegativeFloat(const char prompt[]);
float calculateSalary(float basic, float housing, float transport);
void printEmployee(int i);
void AddEmployee(void);
void displayEmployeeDetails(void);
void SearchEmployee(void);
void CalculateBasicSalary(void);

#endif