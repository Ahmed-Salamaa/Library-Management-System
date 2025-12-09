#include <bits/stdc++.h>
using namespace std;

// Include all headers in correct order
#include "LinkedList.h"
#include "Utilities.h"
#include "System.h"
#include "User.h"
#include "Book.h"
#include "Borrow.h"
#include "Student.h"
#include "Admin.h"

// ========== Initialize static members HERE ONLY ==========
LinkedList<User *> User::UserTable;
LinkedList<Book *> Book::BookTable;
LinkedList<Borrow *> Borrow::BorrowTable;

// Start IDs higher than the loaded data to avoid conflicts
int User::ID_START = 1000003;   // Last user ID is 1000003
int Book::ID_START = 2000005;   // Last book ID is 2000005
int Borrow::ID_START = 3000000; // No borrows loaded yet

User *System::currPtr = nullptr;
bool System::systemState = false;
// ========================================================

// Loads initial data into the system (simulates loading from a file).
// Creates sample books, an admin account, and student accounts.
void loadInitialData()
{
    cout << "Loading initial data...\n";

    // Create initial books (BEFORE system starts)
    new Book(2000001, 5, "C++ Programming", "Bjarne Stroustrup");
    new Book(2000002, 3, "Clean Code", "Robert Martin");
    new Book(2000003, 7, "Design Patterns", "Gang of Four");
    new Book(2000004, 2, "The Pragmatic Programmer", "Hunt & Thomas");
    new Book(2000005, 4, "Introduction to Algorithms", "Cormen");

    // Create initial admin (BEFORE system starts)
    new Admin(1000001, "Admin User", "admin", "Admin@123");

    // Create initial students (BEFORE system starts)
    new Student(1000002, "Rasha Jouda", "rasha", "Rasha@123");
    new Student(1000003, "Sara Ali", "sara", "Sara@123");

    cout << "✓ Initial data loaded successfully!\n\n";
}

// Handles the login process for users.
// @return: A pointer to the logged-in User object, or nullptr if login is cancelled.
User *login()
{
    cout << "\n╔═══════════════════════════════════════╗\n";
    cout << "║     Library Management System         ║\n";
    cout << "║              LOGIN                    ║\n";
    cout << "╚═══════════════════════════════════════╝\n\n";

    while (true)
    {
        try
        {
            cout << "Enter username (or 'exit' to quit): ";
            string username = Utilities::readString(cin, cout);

            cout << "Enter password: ";
            string password = Utilities::readString(cin, cout);

            User *user = User::getPointer(username);

            if (user && user->getPassword() == password)
            {
                cout << "\n✓ Login successful!\n";
                cout << "Welcome, " << user->getName() << "!\n";
                return user;
            }
            else
            {
                cout << "\n✗ Invalid username or password. Please try again.\n\n";
            }
        }
        catch (runtime_error &e)
        {
            if (string(e.what()) == "User requested exit")
            {
                return nullptr;
            }

            cout << "\n✗ Invalid username or password. Please try again.\n\n";
        }
    }
}

User *signup()
{
    cout << "\n╔═══════════════════════════════════════╗\n";
    cout << "║     Library Management System         ║\n";
    cout << "║             SIGN UP                   ║\n";
    cout << "╚═══════════════════════════════════════╝\n\n";

    try
    {
        cout << "Enter full name: ";
        string name = Utilities::readString();

        cout << "Enter username: ";
        string username = Utilities::readUsername();

        User *exist = nullptr;
        try
        {
            exist = User::getPointer(username);
        }
        catch (...)
        {
            exist = nullptr;
        }

        if (exist != nullptr)
        {
            throw runtime_error("Username already exists.");
        }

        cout << "Enter password: ";
        string password = Utilities::readPassword();

        User *newUser = new Student(name, username, password);
        cout << "✓ User created successfully!\n";
        return newUser;
    }
    catch (const runtime_error &e)
    {
        if (string(e.what()) == "User requested exit")
            throw;
        cerr << "Error: " << e.what() << endl;
        return nullptr;
    }
    catch (...)
    {
        cout << "Unknown error occurred while adding user." << endl;
        return nullptr;
    }
}

// Displays the main menu before login and handles user authentication.
void mainMenu()
{
    while (true)
    {
        try
        {
            string menuName = "Library Management System";
            vector<string> menu = {"Login", "signup", "Exit"};

            int choice = Utilities::printMenu(menuName, menu, cout);

            if (choice == 1)
            {
                User *loggedInUser = login();

                if (loggedInUser)
                {
                    System::currPtr = loggedInUser;

                    if (loggedInUser->getType() == 2)
                    {
                        // Admin
                        Admin *admin = dynamic_cast<Admin *>(loggedInUser);
                        admin->mainMenu();
                    }
                    else
                    {
                        // Student
                        Student *student = dynamic_cast<Student *>(loggedInUser);
                        student->mainMenu();
                    }

                    cout << "\n✓ Logged out successfully.\n";
                }
            }
            else if (choice == 2)
            {
                User *newUser = signup();
                if (newUser)
                {
                    cout << "\nUser added successfully\n";
                    User *loggedInUser = login();
                    if (loggedInUser)
                    {
                        System::currPtr = loggedInUser;

                        if (loggedInUser->getType() == 2)
                        {
                            // Admin
                            Admin *admin = dynamic_cast<Admin *>(loggedInUser);
                            admin->mainMenu();
                        }
                        else
                        {
                            // Student
                            Student *student = dynamic_cast<Student *>(loggedInUser);
                            student->mainMenu();
                        }

                        cout << "\n✓ Logged out successfully.\n";
                    }
                }
                else
                {
                    cout << "\nSignup failed. Please try again.\n";
                }
            }
            else if (choice == 3)
            {
                cout << "\nThank you for using Library Management System. Goodbye!\n";
                break;
            }
        }
        catch (runtime_error &e)
        {
            if (string(e.what()) == "User requested exit")
            {
                cout << "\nThank you for using Library Management System. Goodbye!\n";
                break;
            }
            else
            {
                cout << "Error: " << e.what() << "\n";
            }
        }
    }
}

// Main entry point of the program.
// Initializes the system, loads data, and displays the main menu.
int main()
{
    try
    {
        // Load initial data BEFORE system starts
        // (systemState is still false)
        loadInitialData();

        // NOW start the system (systemState = true)
        // ID_START values are automatically managed by the classes
        System::Start_System();

        cout << "\n╔═══════════════════════════════════════════════════════╗\n";
        cout << "║                                                       ║\n";
        cout << "║     Welcome to Library Management System!            ║\n";
        cout << "║                                                       ║\n";
        cout << "╚═══════════════════════════════════════════════════════╝\n";

        cout << "\n📚 Test Accounts:\n";
        cout << "----------------------------------------\n";
        cout << "Admin Login:\n";
        cout << "  Username: admin\n";
        cout << "  Password: Admin@123\n";
        cout << "----------------------------------------\n";
        cout << "Student Login:\n";
        cout << "  Username: rasha\n";
        cout << "  Password: Rasha@123\n";
        cout << "----------------------------------------\n\n";

        // Display main menu
        mainMenu();
    }
    catch (exception &e)
    {
        cout << "Fatal Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}