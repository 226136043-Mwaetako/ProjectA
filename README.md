Municipal Financial Management System

Group Number: 21 
Course: PAP521S- Programming In Practice
Language: C

GROUP MEMBERS
Student 1 EMPLOYEE MANAGEMENT- Lazarus Jessica (226029905),
Student 2 BUDGET MANAGEMENT- Gideon Vistolina (226082377),
Student 3 SUPPLIER MANAGEMENT- Delcy Guriras (226041611),
Student 4 ASSET MANAGEMENT- Festus (225150522),
Student 5 REPORTS-Uusiku (Bonifatius 225034581),
Student 6 FUNCTIONS, INTEGRATION AND VALIDATION-Twalukeni Hilaria (226068420),
Student 7 TESTING, DOCUMENTATION AND GIT COORDINATION- Meilikano Mwaetako (226136043)    

ABOUT THE PROJECT:
The Municipal Financial Management System is a C-based system produced to manage municipal 
financial information. The system shows modules for managing the roles provided above.

SYSTEM FEATURES
The system includes the following modules:
-Employee Management
-Budget Management 
-Supplier Management
-Asset Management
-Reports
-Input Validation
-System Integration

## How to run

1. Clone the repo and switch to the main branch:
   git clone https://github.com/226136043-Mwaetako/ProjectA.git
   cd ProjectA
   git checkout main

2. Compile (needs gcc, C99):
   gcc -std=c99 -Wall -Wextra main.c EmployeeManagement.c budget.c supplier.c assets.c reports.c Validation.c -o mfms

3. Run:
   Windows:   .\mfms
   Linux/Mac: ./mfms
