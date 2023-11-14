#include<stdio.h>
#include<math.h>
#include <string.h>
#define MAX_LENGTH 20

int userProfile();

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


//user signin
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
        userProfile();
    } else {
        printf("Invalid User credentials\n");
    }
    return 0;
}

//expense calculator
int userProfile() {

    printf("WELCOME TO THE HOUSEHOLD BUDGET MANAGEMENT SYSTEM");
    printf("\n");
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
    if (expenseDescription[strlen(expenseDescription) - 1] == '\n') {
        expenseDescription[strlen(expenseDescription) - 1] = '\0';
    }

    printf("Enter date of expense (YYYY-MM-DD): ");
    fgets(dateOfExpense, MAX_LENGTH, stdin);

    // Remove the newline character from dateOfExpense if present
    if (dateOfExpense[strlen(dateOfExpense) - 1] == '\n') {
        dateOfExpense[strlen(dateOfExpense) - 1] = '\0';
    }

    // Open the file for writing in append mode
    FILE *file = fopen("user_profile.txt", "a");
    if (file == NULL) {
        printf("Error: Unable to open file for writing\n");
        return 0;
    }

    float saving = monthlySalary - expenseAmount;

    // Write user inputs to the file
    fprintf(file, "Monthly Salary: %.2f\n", monthlySalary);
    fprintf(file, "Expense Amount: %.2f\n", expenseAmount);
    fprintf(file, "Expense Description: %s\n", expenseDescription);
    fprintf(file, "Date of Expense: %s\n", dateOfExpense);
    fprintf(file, "Saving: %.2f\n", saving);

    dashboard();

    // Close the file
    fclose(file);

    // Display a message
    printf("User profile saved successfully.\n");
    return 0;
}


int readUserProfile() {
    // Open the file for reading
    FILE *file = fopen("user_profile.txt", "r");
    if (file == NULL) {
        printf("Error: Unable to open file for reading\n");
        return;
    }

    // Read and print information from the file
    char buffer[MAX_LENGTH];
    while (fgets(buffer, MAX_LENGTH, file) != NULL) {
        printf("%s", buffer);
    }

    // Close the file
    fclose(file);

    return 0;
}

int dashboard() {
    printf("\nDashboard:\n");
    printf("-------------\n");
    readUserProfile();
    printf("-------------\n");
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


//Main function
int main(){
    int value;
    printf("Welcome To HouseHold Budget management System");
    printf("\n\n");
    printf("Existing User Sign In (Enter 1)");
    printf("\n\n");
    printf("New User Register (Enter 2)");
    printf("\n\n");

    //user Uthentication gateway
    printf("Enter a value 1 or 2 to proceed: ");
    scanf("%d", &value); 
    printf("\n");
    if (value==1){
        signInAuth();
    }else if(value==2){
        registerUser();
    }else{
        printf("Unavailable Input");
    }
    printf("\n\n");


    return 0;
}