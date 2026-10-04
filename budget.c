#include <stdio.h>
#include <string.h>
#include "budget.h"

struct Budget budgets[MAX_DEPARTMENTS];
int budgetCount = 0;

// This is the function they will ask you to show in demo
float getBudgetBalance(float allocated, float expenditure) {
    return allocated - expenditure;
}

int isWithinBudget(float remaining) {
    return remaining >= 0;
}

void addBudget() {
    if (budgetCount >= MAX_DEPARTMENTS) {
        printf("Budget database full!\n");
        return;
    }

    struct Budget b;
    b.id = budgetCount + 1;

    printf("Enter Department Name: ");
    scanf(" %[^\n]", b.department);

    if (strlen(b.department) == 0) {
        printf("Error: Department name cannot be empty!\n");
        return;
    }

    printf("Enter Allocated Budget N$: ");
    scanf("%f", &b.allocated);
    if (b.allocated < 0) {
        printf("Error: Negative budget not allowed!\n");
        return;
    }

    printf("Enter Expenditure N$: ");
    scanf("%f", &b.expenditure);
    if (b.expenditure < 0) {
        printf("Error: Negative expenditure not allowed!\n");
        return;
    }

    b.remaining = getBudgetBalance(b.allocated, b.expenditure);

    budgets[budgetCount] = b;
    budgetCount++;

    printf("\nDepartment '%s' added successfully!\n", b.department);
    printf("Remaining Budget: N$%.2f\n", b.remaining);
    printf("Status: %s\n", isWithinBudget(b.remaining)? "WITHIN BUDGET" : "EXCEEDED BUDGET");
}

void calculateRemainingBudgets() {
    for (int i = 0; i < budgetCount; i++) {
        budgets[i].remaining = getBudgetBalance(budgets[i].allocated, budgets[i].expenditure);
    }
}

void displayBudgets() {
    if (budgetCount == 0) {
        printf("No budgets entered yet.\n");
        return;
    }

    calculateRemainingBudgets();

    printf("\n========================================\n");
    printf(" BUDGET REPORT\n");
    printf("========================================\n");
    for (int i = 0; i < budgetCount; i++) {
        printf("Department: %s\n", budgets[i].department);
        printf("Allocated Budget: N$%.2f\n", budgets[i].allocated);
        printf("Expenditure: N$%.2f\n", budgets[i].expenditure);
        printf("Remaining Budget: N$%.2f\n", budgets[i].remaining);
        printf("Status: %s\n", isWithinBudget(budgets[i].remaining)? "WITHIN BUDGET" : "EXCEEDED BUDGET");
        printf("----------------------------------------\n");
    }
}

void searchBudget() {
    char searchName[50];
    printf("Enter Department name to search: ");
    scanf(" %[^\n]", searchName);

    for (int i = 0; i < budgetCount; i++) {
        if (strcmp(budgets[i].department, searchName) == 0) {
            printf("\nFound!\n");
            printf("Department: %s\n", budgets[i].department);
            printf("Allocated: N$%.2f\n", budgets[i].allocated);
            printf("Expenditure: N$%.2f\n", budgets[i].expenditure);
            printf("Remaining: N$%.2f\n", budgets[i].remaining);
            printf("Status: %s\n", isWithinBudget(budgets[i].remaining)? "WITHIN BUDGET" : "EXCEEDED BUDGET");
            return;
        }
    }
    printf("Department '%s' not found.\n", searchName);
}

void showExceededBudgets() {
    int found = 0;
    printf("\n--- Departments EXCEEDING Budget ---\n");
    for (int i = 0; i < budgetCount; i++) {
        if (budgets[i].remaining < 0) {
            printf("%s : Over by N$%.2f (Allocated: %.2f, Spent: %.2f)\n",
                   budgets[i].department, -budgets[i].remaining,
                   budgets[i].allocated, budgets[i].expenditure);
            found = 1;
        }
    }
    if (!found) {
        printf("All departments are WITHIN BUDGET.\n");
    }
}

void budgetMenu() {
    int choice;
    do {
        printf("\n=== BUDGET MANAGEMENT ===\n");
        printf("1. Enter Departmental Budget\n");
        printf("2. Display Budget Information\n");
        printf("3. Search Budget by Department\n");
        printf("4. Show Departments Exceeding Budget\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addBudget(); break;
            case 2: displayBudgets(); break;
            case 3: searchBudget(); break;
            case 4: showExceededBudgets(); break;
            case 5: break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while(choice!= 5);
}