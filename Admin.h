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
        Admin ( int id , string name , string username , string password )
            : User( id , 2 , name , username , password ) {}

        // Initializes an Admin object with an auto-generated ID (used during runtime).
        // @param name: The full name of the admin.
        // @param username: The login username of the admin.
        // @param password: The password for authentication.
        Admin ( string name , string username , string password )
            : User( 2 , name , username , password ) {}

        // Displays the main menu for an admin.
        // Overrides the virtual method from the User class.
        void mainMenu () override ;
} ;

#endif