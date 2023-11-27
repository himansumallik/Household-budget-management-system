#include <stdio.h>
#include <string.h>
#define MAX_LENGTH 100

// Function prototypes
int userProfile();
int authenticate(const char *username, const char *password);
int signInAuth();
int homepage();
int userProfile();
int readUserProfile();
int dashboard();
int registerUser();


// Function to authenticate a user
int authenticate(const char *username, const char *password) {
    // Open the file for reading
    FILE *file = fopen("user_data.txt", "r");
    if (file == NULL) {
        printf("Error: Unable to open file for reading\n");
        return 0; // Authentication failed
    }

    char storedUsername[MAX_LENGTH];
    char storedPassword[MAX_LENGTH];

    // Read the file line by line
    while (fscanf(file, "%s %s", storedUsername, storedPassword) == 2) {
        // Check if the provided credentials match the stored credentials
        if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0) {
            fclose(file);
            return 1; // Authentication successful
        }
    }
    fclose(file);
    return 0; // Authentication failed
}

// User signin
int signInAuth() {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("\n");

    printf("Enter your password: ");
    scanf("%s", password);
    printf("\n");

    if (authenticate(username, password)) {
        homepage();
    } else {
        printf("Invalid User credentials\n");
    }
    return 0;
}

// Page after authentication success
int homepage() {
    int inputValue;
    printf("WELCOME TO HOUSEHOLD BUDGET MANAGEMENT SYSTEM");
    printf("\n");
    printf("||Your Dashboard|| <<<Enter 1>>>");
    printf("\n");
    printf("||Enter New Expense|| <<<Enter 2>>>)");
    printf("\n\n");
    printf("Your input(1 or 2): ");
    scanf("%d", &inputValue);
    if (inputValue == 1) {
        dashboard();
    } else if (inputValue == 2) {
        userProfile();
    } else {
        printf("Invalid Input\n");
    }

    return 0;
}

// Expense calculator and user profile
int userProfile() {
    printf("WELCOME TO THE HOUSEHOLD BUDGET MANAGEMENT SYSTEM\n");

    // Declare variables to store user inputs
    float monthlySalary, expenseAmount;
    char expenseDescription[MAX_LENGTH], dateOfExpense[MAX_LENGTH];

    // Get user inputs
    printf("Enter your monthly salary: ");
    scanf("%f", &monthlySalary);

    printf("Enter expense amount: ");
    scanf("%f", &expenseAmount);

    // Consume the newline character left in the input buffer
    getchar();

    printf("Enter expense description: ");
    fgets(expenseDescription, MAX_LENGTH, stdin);

    // Remove the newline character from expenseDescription if present
    size_t len = strlen(expenseDescription);
    if (len > 0 && expenseDescription[len - 1] == '\n') {
        expenseDescription[len - 1] = '\0';
    }

    printf("Enter date of expense (YYYY-MM-DD): ");
    fgets(dateOfExpense, MAX_LENGTH, stdin);

    // Remove the newline character from dateOfExpense if present
    len = strlen(dateOfExpense);
    if (len > 0 && dateOfExpense[len - 1] == '\n') {
        dateOfExpense[len - 1] = '\0';
    }

    float saving = monthlySalary - expenseAmount;

    // Open the files for writing in append mode
    FILE *userExpenseDate = fopen("userExpenseDate.txt", "a");
    FILE *userExpenseAmount = fopen("userExpenseAmount.txt", "a");
    FILE *userExpenseDetails = fopen("userExpenseDetails.txt", "a");
    FILE *userSalary = fopen("userSalary.txt", "a");

    if (userExpenseDate == NULL || userExpenseAmount == NULL || userExpenseDetails == NULL ||
        userSalary == NULL ) {
        printf("Error: Unable to open one or more files for writing\n");
        return 0;
    }

    // Write user inputs to the files
    fprintf(userSalary, "%.2f\n", monthlySalary);
    fprintf(userExpenseAmount, "%.2f\n", expenseAmount);
    fprintf(userExpenseDetails, "%s\n", expenseDescription);
    fprintf(userExpenseDate, "%s\n", dateOfExpense);

    // Close the files
    fclose(userExpenseAmount);
    fclose(userExpenseDate);
    fclose(userExpenseDetails);
    fclose(userSalary);

    // Display a message
    printf("\n");
    printf("User profile saved successfully.\n");
    printf("\n");

    //display dashboard
    int dash;
    printf("Enter 1 to view the dashboard: ");
    scanf("%d",&dash);
    if(dash==1){
        dashboard();
    }
    return 0;
}

// Read user profile
int readUserProfile() {
    // Open the files for reading
    FILE *userExpenseDate = fopen("userExpenseDate.txt", "r");
    FILE *userExpenseAmount = fopen("userExpenseAmount.txt", "r");
    FILE *userSalary = fopen("userSalary.txt", "r");
    FILE *userExpenseDetails = fopen("userExpenseDetails.txt", "r");

    // Check if any of the files couldn't be opened
    if (userExpenseDate == NULL || userSalary == NULL ||
        userExpenseDetails == NULL || userExpenseAmount == NULL) {
        printf("Error: Unable to open one or more files for reading\n");

        // Close any opened files before returning
        if (userExpenseDate != NULL) fclose(userExpenseDate);
        if (userSalary != NULL) fclose(userSalary);
        if (userExpenseDetails != NULL) fclose(userExpenseDetails);
        if (userExpenseAmount != NULL) fclose(userExpenseAmount);

        return -1;  // Return an error code
    }

    // Declare variables to store data
    char date[MAX_LENGTH];
    float salary, expense, saving;
    char description[MAX_LENGTH];

    // Variable to store the first value of userSalary
    float initialSalary;

    // Read the first value of userSalary
    if (fscanf(userSalary, "%f", &initialSalary) != 1) {
        printf("Error: Unable to read initial salary\n");

        // Close the files before returning
        fclose(userExpenseDate);
        fclose(userSalary);
        fclose(userExpenseDetails);
        fclose(userExpenseAmount);

        return -1;  // Return an error code
    }

    // Variable to store the sum of all expenses
    float totalExpenses = 0.0;

    printf("Monthly Salary: %.2f\n", initialSalary);
    printf("-----------------------------------------------------------------\n");
    printf("\n");

    // Print header
    printf("%-20s %-20s %-20s \n", "Date", "Expense Amount", "Expense Details");

    // Read and print information from the files
    while (fscanf(userExpenseDate, "%s", date) == 1) {
        // Set the salary to the initial value
        salary = initialSalary;

        fscanf(userExpenseAmount, "%f", &expense);
        fscanf(userExpenseDetails, "%s", description);

        // Add the expense to the total
        totalExpenses += expense;

        // Calculate saving by subtracting the expense from the salary
        saving = salary - totalExpenses;
        

        // Print the read values
        printf("%-20s %-20.2f %-20s\n", date, expense, description);
    }

    // Print the sum of all expenses
    printf("\n");
    printf("-----------------------------------------------------------------\n");
    printf("Total Savings: %.2f\n", saving);

    // Close the files
    fclose(userExpenseDate);
    fclose(userSalary);
    fclose(userExpenseDetails);
    fclose(userExpenseAmount);

    return 0;
}




// Dashboard
int dashboard() {
    printf("-----------------------------------------------------------------\n");
    printf("************************DASHBOARD********************************\n");
    printf("-----------------------------------------------------------------\n");
    readUserProfile();
    printf("-----------------------------------------------------------------\n");
    printf("*****************************************************************\n");
    printf("-----------------------------------------------------------------\n");
    return 0;
}

// New User registration
int registerUser() {
    char newUsername[MAX_LENGTH];
    char newPassword[MAX_LENGTH];

    printf("Enter a new username: ");
    scanf("%s", newUsername);
    printf("\n");

    printf("Enter a new password: ");
    scanf("%s", newPassword);
    printf("\n");

    // Store the new credentials in a file (e.g., user_data.txt)
    FILE *file = fopen("user_data.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %s\n", newUsername, newPassword);
        fclose(file);
        printf("User registered successfully\n");
    } else {
        printf("Error: Unable to open file for writing\n");
    }
    return 0;
}

// Main function
int main() {
    int value;
    printf("Welcome To HouseHold Budget Management System\n");
    printf("\nExisting User Sign In (Enter 1)\n");
    printf("New User Register (Enter 2)\n");

    // User Authentication gateway
    printf("Enter a value 1 or 2 to proceed: ");
    scanf("%d", &value);
    printf("\n");

    switch (value) {
        case 1:
            signInAuth();
            break;
        case 2:
            registerUser();
            break;
        default:
            printf("Unavailable Input\n");
    }

    printf("\n\n");
    return 0;
}
