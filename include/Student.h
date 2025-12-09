#ifndef FILE_STUDENT
#define FILE_STUDENT

#include <bits/stdc++.h>
using namespace std;

#include "Book.h"
#include "Borrow.h"
#include "User.h"

class Student : public User
{
public:
    // Initializes a Student object with a predefined ID (used during system initialization).
    // @param id: The unique identifier for the student (must be set before system starts).
    // @param name: The full name of the student.
    // @param username: The login username of the student.
    // @param password: The password for authentication.
    Student(int id, string name, string username, string password) ;

    // Initializes a Student object with an auto-generated ID (used during runtime).
    // @param name: The full name of the student.
    // @param username: The login username of the student.
    // @param password: The password for authentication.
    Student(string name, string username, string password) ;

    // Displays the main menu for a student.
    // Overrides the virtual method from the User class.
    void mainMenu() override ;

private:
    // Searches for and displays a book by its title.
    static void studentViewBookByTitle() ;

    // Searches for and displays books by a specific author.
    static void studentViewBooksByAuthor() ;

    // Returns a borrowed book to the library.
    static void studentReturnBook() ;

    // Borrows a book from the library.
    static void studentBorrowBook() ;
};

#endif