#ifndef BUDGET_H
#define BUDGET_H

#define MAX_DEPARTMENTS 50

struct Budget {
    int id;
    char department[50];
    float allocated;
    float expenditure;
    float remaining;
};

void budgetMenu();
void addBudget();
void displayBudgets();
void searchBudget();
void calculateRemainingBudgets();
void showExceededBudgets();
float getBudgetBalance(float allocated, float expenditure);
int isWithinBudget(float remaining);

#endif


