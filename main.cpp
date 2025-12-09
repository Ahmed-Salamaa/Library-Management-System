#include <bits/stdc++.h>
using namespace std;

// Include all headers in correct order
#include "include/LinkedList.h"
#include "include/Utilities.h"
#include "include/System.h"
#include "include/User.h"
#include "include/Book.h"
#include "include/Borrow.h"
#include "include/Student.h"
#include "include/Admin.h"


// Loads initial data into the system (simulates loading from a file).
// Creates sample books, an admin account, and student accounts.
void loadInitialData()
{
    cout << "Loading initial data...\n";

    // Create initial books (BEFORE system starts)
    new Book( 5, "C++ Programming", "Bjarne Stroustrup");
    new Book( 3, "Clean Code", "Robert Martin");
    new Book( 7, "Design Patterns", "Gang of Four");
    new Book( 2, "The Pragmatic Programmer", "Hunt & Thomas");
    new Book( 4, "Introduction to Algorithms", "Cormen");

    // Create initial admin (BEFORE system starts)
    new Admin( "Admin User", "admin", "Admin@123");

    // Create initial students (BEFORE system starts)
    new Student( "Rasha Jouda", "rasha", "Rasha@123");
    new Student( "Sara Ali", "sara", "Sara@123");

    cout << "✓ Initial data loaded successfully!\n\n";
}


// Main entry point of the program.
// Initializes the system, loads data, and displays the main menu.
int main()
{
    try
    {
        // NOW start the system (systemState = true)
        // ID_START values are automatically managed by the classes
        System::Start_System();

        // Load initial data
        loadInitialData();

        string welcomeMsg = "Welcome to Library Management System!" ;
        Utilities::printData( welcomeMsg , cout ) ;

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
        System::mainMenu();
    }
    catch (exception &e)
    {
        cout << "Fatal Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}