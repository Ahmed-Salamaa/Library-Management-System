#ifndef FILE_SYSTEM
#define FILE_SYSTEM

#include <bits/stdc++.h>
using namespace std;

#include "LinkedList.h"
#include "Utilities.h"

// Forward declarations
class User;
class Book;
class Student;
class Admin;
class Borrow;

class System
{
private:
    static bool systemState;

public:
    static User *currPtr;

    // Checks whether the system has been started.
    // @return: True if the system has been initialized, false otherwise.
    static bool isSystemStarted() { return systemState; }

    // Starts the system (transitions from initialization to runtime mode).
    static void Start_System()
    {
        if (isSystemStarted())
            throw runtime_error("You cann't Start Started System");

        loadData();
        systemState = true;
    }
    // Loads data from files (to be implemented)
    static void loadData()
    {
        // TODO: Load data from files
        cout << "Loading data from files...\n";
    }

    // Saves data to files (to be implemented)
    static void saveData()
    {
        // TODO: Save data to files
        cout << "Saving data to files...\n";
    }
};


#endif