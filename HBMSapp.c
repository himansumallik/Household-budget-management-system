#include<stdio.h>
#include<math.h>
#define MAX_LENGTH 20


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
void signInAuth() {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("\n");

    printf("Enter your password: ");
    scanf("%s", password);
    printf("\n");

    if (authenticate(username, password)) {
        printf("Login Successful\n");
    } else {
        printf("Invalid User credentials\n");
    }
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
}




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