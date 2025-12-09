#ifndef FILE_USER
#define FILE_USER

#include <bits/stdc++.h>
using namespace std;

#include "LinkedList.h"
#include "Utilities.h"
#include "System.h"

class System;
class User
{
private:
    static LinkedList<User *> UserTable;
    static int ID_START;

protected:
    const int id;
    // type = 1 for Student
    // type = 2 for Admin
    int type;
    string name;
    const string username;
    string password;

public:
    // Retrieves a pointer to a User object by its ID.
    // @param id: The ID of the user to search for.
    // @return A pointer to the User object if found, or nullptr otherwise.
    // @throws runtime_error: If no user with the given ID exists.
    static User *getPointer(int id) ;

    // Retrieves a pointer to a User object by their username.
    // @param Username: The username to search for.
    // @return A pointer to the User object if found, or nullptr otherwise.
    // @throws runtime_error: If no user with the given username exists.
    static User *getPointer(string Username) ;

    // Deletes a User object from the user table using a pointer reference.
    // @param ptr: A pointer to the User object to delete.
    // @throws runtime_error: If the pointer is invalid (nullptr).
    static void deleteUser(User *ptr) ;

    // Deletes a User object from the user table using their ID.
    // @param id: The ID of the user to delete.
    // @throws runtime_error: If no user with the given ID exists.
    static void deleteUser(int id) ;

    // Initializes a User object with a predefined ID (used during system initialization).
    // @param id: The unique identifier for the user (must be set before system starts).
    // @param type: The type of user (1 for Student, 2 for Admin).
    // @param name: The full name of the user.
    // @param username: The login username of the user.
    // @param password: The password for authentication.
    // @throws runtime_error: If called after the system has started.
    User(int id, int type, string name, string username, string password) ;

    // Initializes a User object with an auto-generated ID (used during runtime).
    // @param type: The type of user (1 for Student, 2 for Admin).
    // @param name: The full name of the user.
    // @param username: The login username of the user.
    // @param password: The password for authentication.
    // @throws runtime_error: If called before the system has started.
    User(int type, string name, string username, string password) ;

    virtual ~User() ;

    // Overloads the << operator to output user profile information in a formatted display.
    // @param out: The output stream to write to.
    // @param obj: The User object whose profile will be displayed.
    // @return The output stream reference for chaining.
    friend ostream &operator<<(ostream &out, const User &obj) ;

    // Retrieves the unique identifier of this user.
    // @return The ID of the user.
    int getId() ;

    string getPassword() ;

    // Retrieves the full name of this user.
    // @return The name as a string.
    string getName() ;

    // Sets the name of this user.
    // @param value: The new name for the user.
    void setName(string value) ;

    // Retrieves the login username of this user.
    // @return The username as a string.
    string getUsername() ;

    // Retrieves the type of this user.
    // @return The user type (1 for Student, 2 for Admin).
    int getType() ;

    // Sets the type of this user.
    // @param value: The new user type (1 for Student, 2 for Admin).
    void setType(int value) ;

    // Displays the main menu for the user.
    // This is a virtual method to be overridden by subclasses (Student, Admin).
    virtual void mainMenu() = 0;

    // Displays the user account management menu.
    // Provides options for viewing profile, changing password, and logging out.
    void userMenu() ;

    // Implementation in main.cpp to avoid circular dependency
    static void addUser() ;

    static void updateUserPassword(int id) ;

    void changeCurrentUserPassword() ;

    static void printUser(int Id) ;

    static void PrintAllUsers() ;
};

#endif