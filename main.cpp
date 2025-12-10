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

// Main entry point of the program.
// Initializes the system, loads data, and displays the main menu.
int main()
{
    try
    {
        System::Start_System();
        System::mainMenu();
        System::End_System();
    }
    catch (exception &e)
    {
        cout << "Fatal Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}