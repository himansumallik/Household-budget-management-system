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
    FILE *userSaving = fopen("userSaving.txt", "a");

    if (userExpenseDate == NULL || userExpenseAmount == NULL || userExpenseDetails == NULL ||
        userSalary == NULL || userSaving == NULL) {
        printf("Error: Unable to open one or more files for writing\n");
        return 0;
    }

    // Write user inputs to the files
    fprintf(userSalary, "Monthly Salary: %.2f\n", monthlySalary);
    fprintf(userExpenseAmount, "Expense Amount: %.2f\n", expenseAmount);
    fprintf(userExpenseDetails, "Expense Description: %s\n", expenseDescription);
    fprintf(userExpenseDate, "Date of Expense: %s\n", dateOfExpense);
    fprintf(userSaving, "Saving: %.2f\n", saving);

    dashboard();

    // Close the files
    fclose(userExpenseAmount);
    fclose(userExpenseDate);
    fclose(userExpenseDetails);
    fclose(userSalary);
    fclose(userSaving);

    // Display a message
    printf("User profile saved successfully.\n");
    return 0;
}

// Read user profile
int readUserProfile() {
    // Open the files for reading
    FILE *userExpenseDate = fopen("userExpenseDate.txt", "r");
    FILE *userExpenseAmount = fopen("userExpenseAmount.txt", "r");
    FILE *userSalary = fopen("userSalary.txt", "r");
    FILE *userSaving = fopen("userSaving.txt", "r");
    FILE *userExpenseDetails = fopen("userExpenseDetails.txt", "r");

    // Check if any of the files couldn't be opened
    if (userExpenseDate == NULL || userSalary == NULL || userSaving == NULL ||
        userExpenseDetails == NULL || userExpenseAmount == NULL) {
        printf("Error: Unable to open one or more files for reading\n");

        // Close any opened files before returning
        if (userExpenseDate != NULL) fclose(userExpenseDate);
        if (userSalary != NULL) fclose(userSalary);
        if (userSaving != NULL) fclose(userSaving);
        if (userExpenseDetails != NULL) fclose(userExpenseDetails);
        if (userExpenseAmount != NULL) fclose(userExpenseAmount);


        return -1;  // Return an error code
    }

    // Declare variables to store data
    char date[MAX_LENGTH];
    float salary, expense, saving;
    char description[MAX_LENGTH];

    // Print header
    printf("%-20s %-20s %-20s %-20s %-20s\n", "Monthly Salary", "Date", "Expense Amount", "Expense Details", "Saving");

    // Read and print information from the files
    while (fscanf(userExpenseDate, "%s", date) ==1) {
        fscanf(userSalary, "%f", &salary);
        fscanf(userExpenseAmount, "%f", &expense);
        fscanf(userSaving, "%f", &saving);
        fscanf(userExpenseDetails, "%s", description);

        // Print the read values
        printf("%-20s %-20.2f %-20.2f %-20s %-20.2f\n", date, salary, expense, description, saving);
    }


    // Close the files
    fclose(userExpenseDate);
    fclose(userSalary);
    fclose(userSaving);
    fclose(userExpenseDetails);
    fclose(userExpenseAmount);

    return 0;
}





// Dashboard
int dashboard() {
    printf("----------------------------------\n");
    printf("***********DASHBOARD**************\n");
    printf("----------------------------------\n");
    readUserProfile();
    printf("----------------------------------\n");
    printf("**********************************\n");
    printf("----------------------------------\n");
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
