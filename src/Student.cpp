#include <bits/stdc++.h>
using namespace std;

#include "../include/LinkedList.h"
#include "../include/Utilities.h"
#include "../include/System.h"
#include "../include/User.h"
#include "../include/Book.h"
#include "../include/Borrow.h"
#include "../include/Student.h"

Student::Student(int id, string name, string username, string password)
    : User(id, 1, name, username, password) {}

Student::Student(string name, string username, string password)
    : User(1, name, username, password) {}

void Student::mainMenu()
{
    while (true)
    {
        try
        {
            string menuName = "Student Dashboard";
            vector<string> menu =
                {
                    "Change Password",
                    "View All Books",
                    "View Book by Title",
                    "View Books by Author",
                    "Return Book",
                    "Borrow Book",
                    "Show Borrow History",
                    "View My Profile",
                    "Logout"};

            int choice = Utilities::printMenu(menuName, menu, cout);

            if (choice == 1)
                this->changeCurrentUserPassword();
            else if (choice == 2)
                Book::printAllBooks();
            else if (choice == 3)
                studentViewBookByTitle();
            else if (choice == 4)
                studentViewBooksByAuthor();
            else if (choice == 5)
                studentReturnBook();
            else if (choice == 6)
                studentBorrowBook();
            else if (choice == 7)
                Borrow::GetHistoryByUser();
            else if (choice == 8)
                cout << *this;
            else if (choice == 9)
            {
                cout << "Logging out...\n";
                System::currPtr = nullptr;
                return;
            }
        }
        catch (runtime_error &e)
        {
            if (string(e.what()) == "User requested exit")
            {
                cout << "Returning to menu...\n";
            }
            else
            {
                cout << e.what() << "\n";
            }
        }
    }
}

void Student::studentViewBookByTitle()
{
    cout << "\n========== View Book by Title ==========\n";

    try
    {
        cout << "Enter book title: ";
        string title = Utilities::readString(cin, cout);

        Book *book = Book::getPointer(title);

        if (book)
        {
            cout << *book;
        }
        else
        {
            cout << "Book not found!\n";
        }
    }
    catch (runtime_error &e)
    {
        cout << e.what() << "\n";
    }
}

void Student::studentViewBooksByAuthor()
{
    cout << "\n========== View Books by Author ==========\n";

    try
    {
        cout << "Enter author name: ";
        string author = Utilities::readString(cin, cout);

        Book::viewBooks(author);
    }
    catch (runtime_error &e)
    {
        cout << e.what() << "\n";
    }
}

void Student::studentReturnBook()
{
    cout << "\n========== Return Book ==========\n";

    if (!Borrow::hasAbookToReturn(System::currPtr->getId()))
    {
        cout << "You don't have any books to return.\n";
        return;
    }
    else
    {
        try
        {
            cout << "\n--- Your Currently Borrowed Book ---\n";
            int bookId = Borrow::bookToReturn();
            Book *book = Book::getPointer(bookId);
            cout << book->getTitle() << " by " << book->getAuthor();
            cout << "Are you sure you want to return this book ? (yes/no): ";
            string confirm = Utilities::readString(cin, cout);

            if (confirm == "yes" || confirm == "YES")
            {
                Borrow::changeStatusOfBookForRutern(bookId);
                cout << "✓ Book returned successfully!\n";
            }
            else
            {
                cout << "Operation cancelled.\n";
            }
        }
        catch (runtime_error &e)
        {
            cout << e.what() << "\n";
        }
    }
}

void Student::studentBorrowBook()
{
    cout << "\n========== Borrow Book ==========\n";

    try
    {
        if (Borrow::hasAbookToReturn(System::currPtr->getId()))
        {
            throw runtime_error("Your already has a book ,so you can not borrow book right now");
        }

        cout << "Enter book title to borrow: ";
        string title = Utilities::readString(cin, cout);

        Borrow::borrowBook(System::currPtr->getId(), title);
        cout << "✓ Book borrowed successfully!\n";
    }
    catch (runtime_error &e)
    {
        cout << e.what() << "\n";
    }
}