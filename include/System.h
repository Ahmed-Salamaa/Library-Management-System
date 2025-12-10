#ifndef FILE_SYSTEM
#define FILE_SYSTEM

#include <bits/stdc++.h>
using namespace std;

#include "LinkedList.h"
#include "Utilities.h"
#include "DataManager.h"

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
    static void Start_System();

    static void End_System();

    // Handles the login process for users.
    // @return: A pointer to the logged-in User object, or nullptr if login is cancelled.
    static User * login();

    // Handles the signup process for new users.
    // @return: A pointer to the newly created User object, or nullptr if signup fails.
    static User * signup();

    // Displays the main menu before login and handles user authentication.
    static void mainMenu();
};

#endif