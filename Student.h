#ifndef FILE_STUDENT
#define FILE_STUDENT

#include <bits/stdc++.h>
using namespace std;

#include "User.h"

class Student : public User
{
    public :

        // Initializes a Student object with a predefined ID (used during system initialization).
        // @param id: The unique identifier for the student (must be set before system starts).
        // @param name: The full name of the student.
        // @param username: The login username of the student.
        // @param password: The password for authentication.
        Student ( int id , string name , string username , string password )
            : User( id , 1 , name , username , password ) {}

        // Initializes a Student object with an auto-generated ID (used during runtime).
        // @param name: The full name of the student.
        // @param username: The login username of the student.
        // @param password: The password for authentication.
        Student ( string name , string username , string password )
            : User( 1 , name , username , password ) {}

        // Displays the main menu for a student.
        // Overrides the virtual method from the User class.
        void mainMenu () override ;
} ;

#endif