#include <bits/stdc++.h>
using namespace std;

#include "../include/LinkedList.h"
#include "../include/Utilities.h"
#include "../include/System.h"
#include "../include/User.h"
#include "../include/Book.h"
#include "../include/Borrow.h"
#include "../include/Student.h"
#include "../include/Admin.h"

// Static member definitions
User *System::currPtr = nullptr;
bool System::systemState = false;

void System::Start_System()
{
    if (isSystemStarted())
        throw runtime_error("You cann't Start Started System");

    loadData();
    systemState = true;
}

void System::loadData()
{
    cout << "Loading data from files...\n";
}

void System::saveData()
{
    cout << "Saving data to files...\n";
}

User *System::login()
{
    vector<string> welcomeMsg =
        {
            "Library Management System",
            "LOGIN"};

    Utilities::printData(welcomeMsg, cout);

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

User *System::signup()
{
    vector<string> welcomeMsg =
        {
            "Library Management System",
            "SIGN UP"};

    Utilities::printData(welcomeMsg, cout);

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

void System::mainMenu()
{
    while (true)
    {
        try
        {
            string menuName = "Library Management System";
            vector<string> menu =
                {
                    "Login",
                    "signup",
                    "Exit"};

            int choice = Utilities::printMenu(menuName, menu, cout);

            if (choice == 1)
            {
                User *loggedInUser = login();

                if (loggedInUser)
                {
                    System::currPtr = loggedInUser;
                    currPtr->mainMenu();
                    cout << "\n✓ Logged out successfully.\n";
                }
            }
            else if (choice == 2)
            {
                User *newUser = signup();
                if (newUser)
                {
                    cout << "\nUser added successfully\n";
                    continue;
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