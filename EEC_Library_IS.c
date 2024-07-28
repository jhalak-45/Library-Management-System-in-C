/*
    Project Title: Everest Engineering College Library Information System
    Developer: Jhalak Dhami
    Start Date: 2080/11/20 B.S.
    End Date: 2080/12/01 B.S.
    Submitted Date:2080/12/02 B.S. [March 15, 2024]
    Developer Mail: jhalak.dhami_23@eemc.edu.np (Educational Mail)
    Version: 1.01

    Description:
    This project titled , Everest Engineering College Library Information System (EEC LIS), is designed to manage the library's information effectively.
    It allows users to perform various tasks such as adding, updating, and deleting books, managing user accounts and searching for books.

    Features:
    1.Book mangement
    2.Staff Management
    3.Change password
    4.User Management

    Application Components:
    - Main Menu: Displays options for different functionalities.
    - Manage Book Meny : Allows users to perform book-related operations[Add New, View All,Search,Delete,Update etc...].
    - Manage User Menu : Handles user account-related functionalities like Add New, View All,Search,Delete,Update etc...
    - Manage Staffs: Facilitates to manage  staffs of library(Add New, View All,Search,Delete,Update etc...).
    - Change Password facility
*/

/*Header files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*macros or defined directives*/

// for user
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// for books
#define MAX_TITLE_LENGTH 100
#define MAX_AUTHOR_LENGTH 50
#define MAX_ISBN_LENGTH 20

// for staffs
#define MAX_NAME_LENGTH 50
#define MAX_POSITION_LENGTH 50
#define MAX_ID_LENGTH 20

/* ALL  Structures */

typedef struct
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

typedef struct
{
    char title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    char isbn[MAX_ISBN_LENGTH];
} Books;

typedef struct
{
    char name[MAX_NAME_LENGTH];
    char position[MAX_POSITION_LENGTH];
    char id[MAX_ID_LENGTH];
} Staff;

/* Function Prototypes */
// to create account
void createAccount();
// to login
int login();

// header function for application title
void header();

// main menu for login and create account options
void main_menu();

// function for menu after logged in manage user , books, staffs and channge password
void sub_menu();

/*to manage books menu function [Create,Update,View,Delete,search]...*/
void manage_books();

// function to create new book
void createBook();

// function to view all books
void viewAllBooks();

// for search book by name
void searchBook(const char *title);

// for delete book by book name
void deleteBook(const char *title);

// update book by name
void updateBook(const char *title);
/*to create,update,view and delete users in Librabry */
void manage_users();

// Function prototype to add a new user
void addUser();

// Function to update an existing user
void updateUser();

// Function prototype to delete
void deleteUser();

// Function prototype to view all
void viewAllUsers();

// Function prototype to search for a user
void searchUser();

/*functions to manage staffs , all functions are used in manage staffs  menu*/
void manage_staffs();

// Function to add a new staff record
void addStaff();

// Function to view all staff records
void viewAllStaffs();

// Function to search for a staff record by ID
void searchStaff(const char *id);

// Function to delete a staff record by ID
void deleteStaff(const char *id);

// Function to update a staff record by ID
void updateStaff(const char *id);

void change_password(const char *username, const char *newPassword); // function to change user password

/*  Application main function */
int main()
{
    // main menu function called
    main_menu();
    return 0;
}

/* All functions included in application  */
// function to create user account
void createAccount()
{
    // file open for reading and appending (writing at end of file)
    FILE *file = fopen("users.txt", "a+");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    // user defined structure type User and created structure named newUser
    User newUser;
    system("cls");
    header();
    User existingUser;
    printf("Enter Username: ");
    scanf("%s", newUser.username);
    while (fscanf(file, "%s %s", existingUser.username, existingUser.password) != EOF)
    {
        if (strcmp(newUser.username, existingUser.username) == 0)
        {
            // fclose(file);
            printf("User already exists. chooser another username\n");
            break;
        }
    }
    printf("Enter Password: ");
    scanf("%s", newUser.password);
    if (strlen(newUser.password) < 8)
    {
        fclose(file);
        printf("Password must be greater then 8 character..\n");
    }
    fprintf(file, "%s %s\n", newUser.username, newUser.password);

    // closing file
    fclose(file);
    // clear screen function
    system("cls");
    printf("Account created successfully.\n");
}

// function to login
int login()
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    system("cls");
    header();
    printf("|----------------------------------------------------------|\n");
    printf("|                   Enter Your Credentials                 |\n");
    printf("|----------------------------------------------------------|\n");

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    FILE *file = fopen("users.txt", "r"); // file name users.txt and opened in reading mode
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 0;
    }

    User user;
    while (fscanf(file, "%s %s", user.username, user.password) != EOF)
    {
        // compare user name and user entered password with saved details in file
        if (strcmp(username, user.username) == 0 && strcmp(password, user.password) == 0)
        {
            fclose(file);
            return 1; // if Login successful
        }
    }
    fclose(file);
    return 0; // if login failed
}

// Application Main Menu Function
void main_menu()
{
    int choice;
    do
    {
        system("cls");
        header();
        printf("1. Login\n");
        printf("2. Create Account\n");
        printf("3. Exit\n");

        printf("Enter Your Choice[1-3]: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (login())
            {
                system("cls");
                printf("              Login Successful.      \n");
                sub_menu();
            }
            else
            {
                system("cls");
                printf("Login failed. Invalid username or password.\n");
            }
            break;
        case 2:
            createAccount();
            break;
        case 3:
            printf("Thank You....\n");
            exit(0);
            break;
        default:
            printf("Invalid choice.\n");
            exit(0);
            break;
        }
    } while (choice != 3);
}

// function for submenu it appears after login successful
void sub_menu()
{
    system("cls");
    int choice;
    do
    {
        header();
        printf("1. Manage Books\n");
        printf("2. Manage Staffs\n");
        printf("3. Manage Users\n");
        printf("4. Change Password\n");
        printf("5. Back\n");
        printf("6. Exit\n");
        printf("Enter your Choice[1-6]: ");
        scanf("%d", &choice);
        fflush(stdin);
        switch (choice)
        {
        case 1:
            manage_books();
            break;
        case 2:
            manage_staffs();
            break;
        case 3:
            manage_users();
            break;
        case 4:
        {
            // case for change password
            system("cls");
            printf("|------------------------------------------------------|\n");
            printf("|-------------------- ENTER DETAILS -------------------|\n");
            printf("|------------------------------------------------------|\n");
            char username[MAX_USERNAME_LENGTH];
            char newPassword[MAX_PASSWORD_LENGTH];

            printf("Enter Username: ");
            scanf("%s", username);
            printf("Enter New Password: ");
            scanf("%s", newPassword);
            change_password(username, newPassword);
        }
        break;
        case 5:
            main_menu();
            break;
        case 6:
            exit(0);
            break;
        default:
            printf("Invalid choice\n");
        }
    } while (choice != 6);
}
void manage_books()
{
    system("cls");
    int choice;
    char title[MAX_TITLE_LENGTH];

    do
    {
        header();
        printf("|----------------------  MANAGE BOOKS ---------------------|\n");
        printf("1. Add New\n");
        printf("2. View All \n");
        printf("3. Search\n");
        printf("4. Delete\n");
        printf("5. Update\n");
        printf("6. Back\n");
        printf("7. Exit\n");
        printf("Enter your Choice[1-7]: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            // calling function creatBook
            createBook();
            break;
        case 2:
            // calling function viewAllBooks
            viewAllBooks();
            break;
        case 3:
            // case for search books
            printf("Enter the title of the book to search: ");
            scanf(" %[^\n]", title);
            // function call searchBook with entered title as a parameter
            searchBook(title);
            break;
        case 4:
            // case for delete book
            printf("Enter the title of the book to delete: ");
            scanf(" %[^\n]", title);
            // function call deleteBook with entered title as a parameter
            deleteBook(title);
            break;
        case 5:
            // case for update book
            printf("Enter the title of the book to update: ");
            scanf(" %[^\n]", title);
            updateBook(title);
            break;
        case 6:
            // calling back to sub menu
            sub_menu();
            break;
        case 7:
            // case for exit
            printf("..............Thank You.....\n");
            printf("Exiting...\n");
            exit(0);
            break;
        default:
            printf("Invalid choice.\n");
            exit(0);
            break;
        }
    } while (choice != 7);
}
void manage_staffs()
{
    system("cls");

    int choice;
    char id[MAX_ID_LENGTH];

    do
    {
        header();
        printf("|----------------------  MANAGE STAFFS-------------------|\n\n");
        printf("1. Add New\n");
        printf("2. View All\n");
        printf("3. Search\n");
        printf("4. Update\n");
        printf("5. Delete\n");
        printf("6. Back\n");
        printf("7. Exit\n");
        printf("Enter Your Choice[1-7]: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addStaff();
            break;
        case 2:
            viewAllStaffs();
            break;
        case 3:
        {
            // case for search staff by id as a passing parameter
            system("cls");
            printf("|-------------------------------------------------------------|\n");
            printf("|----------------------  SEARCH STAFF ------------------------|\n");
            printf("|-------------------------------------------------------------|\n");
            printf("Enter the ID of the staff to search: ");
            scanf(" %[^\n]", id);
            searchStaff(id);
        }
        break;
        case 4:
        {
            // case for update staff and passing id as a parameter
            system("cls");
            printf("|------------------------------------------------------------------|\n");
            printf("|----------------------  UPDATE STAFF DETAILS ---------------------|\n");
            printf("|------------------------------------------------------------------|\n");
            printf("Enter the ID of the staff to update: ");
            scanf(" %[^\n]", id);
            updateStaff(id);
        }
        break;
        case 5:
        {
            // case for delete staff and passing id as a parameter
            system("cls");
            printf("|-------------------------------------------------------------|\n");
            printf("|----------------------  DELETE STAFF ------------------------|\n");
            printf("|-------------------------------------------------------------|\n");
            printf("Enter the ID of the staff to delete: ");
            scanf(" %[^\n]", id);
            deleteStaff(id);
        }
        break;
        case 6:
            // case for back to submenu
            sub_menu();
            break;
        case 7:
            // case for exit
            printf("...................Thank You................\n");
            printf("Exiting...\n");
            exit(0);
            break;
        default:
            printf("Invalid choice.\n");
            exit(0);
            break;
        }
    } while (choice != 7);
}

// fucntion for change password
void change_password(const char *username, const char *newPassword)
{
    system("cls");
    header();
    printf("|--------------------- Change Password ----------------------|\n");

    FILE *file = fopen("users.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error opening temporary file.\n");
        fclose(file);
        return;
    }

    User user;
    int found = 0;
    while (fscanf(file, "%s %s", user.username, user.password) != EOF)
    {
        if (strcmp(username, user.username) == 0)
        {
            strcpy(user.password, newPassword);
            found = 1;
        }
        fprintf(tempFile, "%s %s\n", user.username, user.password);
    }

    fclose(file);
    fclose(tempFile);

    if (!found)
    {
        printf("User not found.\n");
        remove("temp.txt");
        return;
    }

    remove("users.txt");
    rename("temp.txt", "users.txt");
    system("cls");
    printf("Password changed successfully.\n");
}

// function to manage user menu
void manage_users()
{
    system("cls");
    int choice;
    do
    {
        header();
        printf("|----------------------  MANAGE USERS --------------------|\n");
        printf("1. Add New\n");
        printf("2. Update\n");
        printf("3. Delete\n");
        printf("4. View All\n");
        printf("5. Search\n");
        printf("6. Back\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addUser();
            break;
        case 2:
            updateUser();
            break;
        case 3:
            deleteUser();
            break;
        case 4:
            viewAllUsers();
            break;
        case 5:
            searchUser();
            break;
        case 6:
            sub_menu();
            break;
        case 7:
            printf("Exiting...\n");
            exit(0);
            break;
        default:
            printf("Invalid choice.\n");
            break;
        }
    } while (choice != 7);
}
// menu parts ended and the operational functions are in below
/*
<---------------|ALL Functions to manage books,staffs,users etc..| ------------------>
-------------------------------------------------------------------
<---------------------Functions for Manage books------------------>
====================================================================
*/

void createBook()
{

    system("cls");
    printf("|------------------------------------------------------------------|\n");
    printf("|----------------------  ADD BOOKS DETAILS ------------------------|\n");
    printf("|------------------------------------------------------------------|\n");

    FILE *file = fopen("books_data.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    Books newBook;
    printf("Enter Book Title: ");
    scanf(" %[^\n]", newBook.title);
    printf("Enter Author Name: ");
    scanf(" %[^\n]", newBook.author);
    printf("Enter ISBN: ");
    scanf(" %[^\n]", newBook.isbn);

    fprintf(file, "%s|%s|%s\n", newBook.title, newBook.author, newBook.isbn);

    fclose(file);
    system("cls");

    printf("Book added successfully.\n");
}

void viewAllBooks()
{
    system("cls");
    printf("|----------------------------------------------------------|\n");
    printf("|-------------------------- ALL BOOKS ---------------------|\n");
    FILE *file = fopen("books_data.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    Books book;
    printf("|----------------------------------------------------------|\n");
    printf("| %-20s | %-20s | %-10s |\n", "Title", "Author", "ISBN");
    printf("|----------------------------------------------------------|\n");

    while (fscanf(file, "%[^|]|%[^|]|%[^\n]\n", book.title, book.author, book.isbn) != EOF)
    {
        printf("| %-20s | %-20s | %-10s |\n", book.title, book.author, book.isbn);
        printf("|----------------------------------------------------------|\n");
    }

    fclose(file);
}

void searchBook(const char *title)
{
    system("cls");
    printf("|-----------------------------------------------------------|\n");
    printf("|----------------------  SEARCH BOOK -----------------------|\n");
    printf("|-----------------------------------------------------------|\n");
    FILE *file = fopen("books_data.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    Books book;
    int found = 0;
    while (fscanf(file, "%[^|]|%[^|]|%[^\n]\n", book.title, book.author, book.isbn) != EOF)
    {
        if (strcmp(title, book.title) == 0)
        {
            printf("| %-20s | %-20s | %-10s |\n", "Title", "Author", "ISBN");
            printf("|----------------------------------------------------------|\n");
            printf("| %-20s | %-20s | %-10s |\n", book.title, book.author, book.isbn);
            printf("|----------------------------------------------------------|\n");
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Book not found.\n");
    }

    fclose(file);
}

void deleteBook(const char *title)
{
    system("cls");
    printf("|----------------------------------------------------------|\n");
    printf("|-------------------------  DELETE BOOK -------------------|\n");
    printf("|----------------------------------------------------------|\n");
    FILE *file = fopen("books_data.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error opening temporary file.\n");
        fclose(file);
        return;
    }

    Books book;
    int found = 0;
    while (fscanf(file, "%[^|]|%[^|]|%[^\n]\n", book.title, book.author, book.isbn) != EOF)
    {
        if (strcmp(title, book.title) != 0)
        {
            fprintf(tempFile, "%s|%s|%s\n", book.title, book.author, book.isbn);
        }
        else
        {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (!found)
    {
        printf("Book not found.\n");
        remove("temp.txt");
        return;
    }

    remove("books_data.txt");
    rename("temp.txt", "books_data.txt");
    system("cls");

    printf("Book deleted successfully.\n");
}

void updateBook(const char *title)
{
    system("cls");
    printf("|-------------------------------------------------------------|\n");
    printf("|-----------------------  UPDATE BOOK ------------------------|\n");
    printf("|-------------------------------------------------------------|\n");
    FILE *file = fopen("books_data.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error opening temporary file.\n");
        fclose(file);
        return;
    }

    Books book;
    int found = 0;
    while (fscanf(file, "%[^|]|%[^|]|%[^\n]\n", book.title, book.author, book.isbn) != EOF)
    {
        if (strcmp(title, book.title) == 0)
        {
            printf("Enter New Title: ");
            scanf(" %[^\n]", book.title);
            printf("Enter New Author: ");
            scanf(" %[^\n]", book.author);
            printf("Enter New ISBN: ");
            scanf(" %[^\n]", book.isbn);
            found = 1;
        }
        fprintf(tempFile, "%s|%s|%s\n", book.title, book.author, book.isbn);
    }

    fclose(file);
    fclose(tempFile);

    if (!found)
    {
        printf("Book not found.\n");
        remove("temp.txt");
        return;
    }

    remove("books_data.txt");
    rename("temp.txt", "books_data.txt");
    system("cls");

    printf("Book updated successfully.\n");
}

/*Books functions end*/

/*
-------------------------------------------------------------------
<--------------------- Functions for Manage Staffs  ------------------>
====================================================================
 */

void addStaff()
{
    FILE *file = fopen("staff_data.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    Staff newStaff;
    system("cls");
    printf("|-----------------------------------------------------------|\n");
    printf("|---------------------  ADD STAFF DETAILS ------------------|\n");
    printf("|-----------------------------------------------------------|\n");
    printf("Enter Staff Name: ");
    scanf(" %[^\n]", newStaff.name);
    printf("Enter Staff Position: ");
    scanf(" %[^\n]", newStaff.position);
    printf("Enter Staff ID: ");
    scanf(" %[^\n]", newStaff.id);

    fprintf(file, "%s|%s|%s\n", newStaff.name, newStaff.position, newStaff.id);

    fclose(file);
    system("cls");
    printf("Staff added successfully.\n");
}

void viewAllStaffs()
{
    FILE *file = fopen("staff_data.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    system("cls");
    printf("|---------------------- ALL STAFFS ------------------------|\n");
    printf("|----------------------------------------------------------|\n");
    printf("| %-20s | %-20s | %-10s |\n", "Name", "Position", "ID");
    printf("|----------------------------------------------------------|\n");

    Staff staff;
    while (fscanf(file, "%[^|]|%[^|]|%[^\n]\n", staff.name, staff.position, staff.id) != EOF)
    {
        printf("| %-20s | %-20s | %-10s |\n", staff.name, staff.position, staff.id);
        printf("|----------------------------------------------------------|\n");
    }

    fclose(file);
}

void searchStaff(const char *id)
{
    FILE *file = fopen("staff_data.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    Staff staff;
    int found = 0;
    while (fscanf(file, "%[^|]|%[^|]|%[^\n]\n", staff.name, staff.position, staff.id) != EOF)
    {
        if (strcmp(id, staff.id) == 0)
        {
            system("cls");
            printf("|----------------------------------------------------------|\n");
            printf("| %-20s | %-20s | %-10s |\n", "Name", "Position", "ID");
            printf("|----------------------------------------------------------|\n");
            printf("| %-20s | %-20s | %-10s |\n", staff.name, staff.position, staff.id);
            printf("|----------------------------------------------------------|\n");
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Staff not found.\n");
    }

    fclose(file);
}

void deleteStaff(const char *id)
{
    FILE *file = fopen("staff_data.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error opening temporary file.\n");
        fclose(file);
        return;
    }

    Staff staff;
    int found = 0;
    while (fscanf(file, "%[^|]|%[^|]|%[^\n]\n", staff.name, staff.position, staff.id) != EOF)
    {
        if (strcmp(id, staff.id) != 0)
        {
            fprintf(tempFile, "%s|%s|%s\n", staff.name, staff.position, staff.id);
        }
        else
        {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (!found)
    {
        printf("Staff not found.\n");
        remove("temp.txt");
        return;
    }

    remove("staff_data.txt");
    rename("temp.txt", "staff_data.txt");
    system("cls");

    printf("Staff deleted successfully.\n");
}

void updateStaff(const char *id)
{
    FILE *file = fopen("staff_data.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error opening temporary file.\n");
        fclose(file);
        return;
    }

    Staff staff;
    int found = 0;
    while (fscanf(file, "%[^|]|%[^|]|%[^\n]\n", staff.name, staff.position, staff.id) != EOF)
    {
        if (strcmp(id, staff.id) == 0)
        {
            printf("Enter New Name: ");
            scanf(" %[^\n]", staff.name);
            printf("Enter New Position: ");
            scanf(" %[^\n]", staff.position);
            printf("Enter New ID: ");
            scanf(" %[^\n]", staff.id);
            found = 1;
        }
        fprintf(tempFile, "%s|%s|%s\n", staff.name, staff.position, staff.id);
    }

    fclose(file);
    fclose(tempFile);

    if (!found)
    {
        printf("Staff not found.\n");
        remove("temp.txt");
        return;
    }

    remove("staff_data.txt");
    rename("temp.txt", "staff_data.txt");
    system("cls");

    printf("Staff updated successfully.\n");
}
/*User Manage Related functions */

// Function to add a new user
void addUser()
{
    createAccount(); // calling to create account function both are same function so
}

// Function to update an existing user
void updateUser()
{
    system("cls");
    printf("|-------------------------------------------------------------|\n");
    printf("|----------------------  UPDATE USER  ------------------------|\n");
    printf("|-------------------------------------------------------------|\n");
    char searchUsername[MAX_USERNAME_LENGTH];
    printf("Enter Username to Update: ");
    scanf("%s", searchUsername);

    FILE *file = fopen("users.txt", "r");
    if (file == NULL)
    {
        system("cls");
        printf("Error opening file.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error opening temporary file.\n");
        fclose(file);
        return;
    }

    User user;
    int found = 0;
    while (fscanf(file, "%s %s", user.username, user.password) != EOF)
    {
        if (strcmp(searchUsername, user.username) == 0)
        {
            printf("Enter New Password: ");
            scanf("%s", user.password);
            found = 1;
        }
        fprintf(tempFile, "%s %s\n", user.username, user.password);
    }

    fclose(file);
    fclose(tempFile);

    if (!found)
    {
        printf("User not found.\n");
        remove("temp.txt");
        return;
    }

    remove("users.txt");
    rename("temp.txt", "users.txt");
    system("cls");
    printf("User updated successfully.\n");
}

// Function to delete an existing user
void deleteUser()
{
    system("cls");
    printf("|------------------------------------------------------------------|\n");
    printf("|----------------------  DELETE USER       ------------------------|\n");
    printf("|------------------------------------------------------------------|\n");
    char searchUsername[MAX_USERNAME_LENGTH];
    printf("Enter Username To Delete: ");
    scanf("%s", searchUsername);

    FILE *file = fopen("users.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error opening temporary file.\n");
        fclose(file);
        return;
    }

    User user;
    int found = 0;
    while (fscanf(file, "%s %s", user.username, user.password) != EOF)
    {
        if (strcmp(searchUsername, user.username) != 0)
        {
            fprintf(tempFile, "%s %s\n", user.username, user.password);
        }
        else
        {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (!found)
    {
        printf("User not found.\n");
        remove("temp.txt");
        return;
    }

    remove("users.txt");
    rename("temp.txt", "users.txt");
    system("cls");
    printf("User deleted successfully.\n");
}

// Function to view all users
void viewAllUsers()
{
    FILE *file = fopen("users.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    system("cls");
    printf("|------------------------------------------------------------------|\n");
    printf("|----------------------  ALL USERS         ------------------------|\n");
    printf("|------------------------------------------------------------------|\n");
    User user;
    printf("| %-10s |\n", "Usernames");
    printf("|------------|\n");

    while (fscanf(file, "%s %s", user.username, user.password) != EOF)
    {
        printf("| %-10s |\n", user.username);
        printf("|------------|\n");
    }

    fclose(file);
}

// Function to search for a user
void searchUser()
{
    char searchUsername[MAX_USERNAME_LENGTH];
    system("cls");
    printf("|------------------------------------------------------------------|\n");
    printf("|----------------------  SEARCH USERS      ------------------------|\n");
    printf("|------------------------------------------------------------------|\n");
    printf("Enter Username: ");
    scanf("%s", searchUsername);

    FILE *file = fopen("users.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    User user;
    int found = 0;
    while (fscanf(file, "%s %s", user.username, user.password) != EOF)
    {
        if (strcmp(searchUsername, user.username) == 0)
        {
            printf("-----------------User found:---------------------\n");
            printf("Username: %s\n", user.username);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("User not found.\n");
    }
}
// application header function

void header()
{
    printf("===========================================================\n");
    printf("=                       WELCOME                           =\n");
    printf("=---------------------------------------------------------=\n");
    printf("=             Everest Engineering College[EEC]            =\n");
    printf("=                                                         =\n");
    printf("=               Library Information System                =\n");
    printf("=                                                         =\n");
    printf("===========================================================\n");
}