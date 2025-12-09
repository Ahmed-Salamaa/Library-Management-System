#ifndef FILE_ADMIN
#define FILE_ADMIN

#include <bits/stdc++.h>
using namespace std;

#include "User.h"

class Admin : public User
{
    public :

        // Initializes an Admin object with a predefined ID (used during system initialization).
        // @param id: The unique identifier for the admin (must be set before system starts).
        // @param name: The full name of the admin.
        // @param username: The login username of the admin.
        // @param password: The password for authentication.
        Admin ( int id , string name , string username , string password ) ;

        // Initializes an Admin object with an auto-generated ID (used during runtime).
        // @param name: The full name of the admin.
        // @param username: The login username of the admin.
        // @param password: The password for authentication.
        Admin ( string name , string username , string password ) ;

        // Displays the main menu for an admin.
        // Overrides the virtual method from the User class.
        // Displays the main menu for an admin.
        // Overrides the virtual method from the User class.
        void mainMenu() override ;

    private:

        static void adminAddUser() ;

        // Updates the password of a user by their ID.
        static void adminUpdateUserPassword() ;

        // Deletes a user from the system by their ID.
        static void adminDeleteUser() ;

        // Searches for and displays a user by their ID.
        static void adminPrintUser() ;

        // Adds a new book to the library system.
        static void adminAddBook() ;

        // Deletes a book from the library system by its ID.
        static void adminDeleteBook() ;

        // Updates book information (title, author, or quantity).
        static void adminUpdateBook() ;

        // Searches for and displays a book by its title.
        static void adminPrintBook() ;
} ;

#endif