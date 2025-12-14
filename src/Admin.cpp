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

Admin::Admin(int id, string name, string username, string password)
    : User(id, 2, name, username, password) {}

Admin::Admin(string name, string username, string password)
    : User(2, name, username, password) {}

void Admin::mainMenu()
{
    while (true)
    {
        try
        {
            string menuName = "Admin Dashboard";
            vector<string> menu =
                {
                    "Add User",
                    "Update User Password",
                    "Delete User",
                    "Print User",
                    "Print All Users",
                    "Change My Password",
                    "Add Book",
                    "Delete Book",
                    "Update Book",
                    "Print Book",
                    "Print All Books",
                    "Logout"};

            int choice = Utilities::printMenu(menuName, menu, cout);

            if (choice == 1)
                adminAddUser();
            else if (choice == 2)
                adminUpdateUserPassword();
            else if (choice == 3)
                adminDeleteUser();
            else if (choice == 4)
                adminPrintUser();
            else if (choice == 5)
                User::PrintAllUsers();
            else if (choice == 6)
                this->changeCurrentUserPassword();
            else if (choice == 7)
                adminAddBook();
            else if (choice == 8)
                adminDeleteBook();
            else if (choice == 9)
                adminUpdateBook();
            else if (choice == 10)
                adminPrintBook();
            else if (choice == 11)
                Book::printAllBooks();
            else if (choice == 12)
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
                cout << "Error: " << e.what() << "\n";
            }
        }
    }
}

void Admin::adminAddUser()
{
    cout << "\n========== Add New User ==========\n";

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

        cout << "Select user type:\n";
        cout << "  1. Student\n";
        cout << "  2. Admin\n";
        cout << "Enter choice: ";
        int userType = Utilities::readInt(1, 2);

        User *newUser = nullptr;

        if (userType == 1)
        {
            newUser = new Student(name, username, password);
            cout << "Student created successfully!\n";
        }
        else
        {
            newUser = new Admin(name, username, password);
            cout << "Admin created successfully!\n";
        }
    }
    catch (const runtime_error &e)
    {
        if (string(e.what()) == "User requested exit")
        {
            throw;
        }
        cerr << "Error: " << e.what() << endl;
    }
    catch (...)
    {
        cout << "Unknown error occurred while adding user." << endl;
    }
}

void Admin::adminUpdateUserPassword()
{
    cout << "\n========== Update User Password ==========\n";

    try
    {
        cout << "Enter user's username : ";
        string username = Utilities::readString(cin, cout);

        User::updateUserPassword(username);
    }
    catch (runtime_error &e)
    {
        cout << "Error: " << e.what() << "\n";
    }
}

void Admin::adminDeleteUser()
{
    cout << "\n========== Delete User ==========\n";

    try
    {
        cout << "Enter user's username to delete: ";
        string username = Utilities::readString(cin, cout);

        User *user = User::getPointer(username);

        if (!user)
        {
            cout << "User not found!\n";
            return;
        }

        if (user->getId() == System::currPtr->getId())
        {
            cout << "Error: Cannot delete yourself!\n";
            return;
        }

        cout << "Are you sure you want to delete user: " << user->getName()
             << " (" << user->getUsername() << ")? (yes/no): ";
        string confirm = Utilities::readString(cin, cout);

        if (confirm == "yes" || confirm == "YES")
        {
            User::deleteUser(username);
            cout << "User deleted successfully!\n";
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

void Admin::adminPrintUser()
{
    cout << "\n========== Print User ==========\n";

    try
    {
        cout << "Enter user's username: ";
        string username = Utilities::readString(cin, cout);

        User::printUser(username);
    }
    catch (runtime_error &e)
    {
        cout << "Error: " << e.what() << "\n";
    }
}

void Admin::adminAddBook()
{
    cout << "\n========== Add New Book ==========\n";

    try
    {
        cout << "Enter book title: ";
        string title = Utilities::readString(cin, cout);

        cout << "Enter author name: ";
        string author = Utilities::readString(cin, cout);

        cout << "Enter quantity: ";
        int quantity = Utilities::readInt(1, 1000, cin, cout);

        Book::addBook(title, author, quantity);
        cout << "Book added successfully!\n";
    }
    catch (runtime_error &e)
    {
        cout << "Error: " << e.what() << "\n";
    }
}

void Admin::adminDeleteBook()
{
    cout << "\n========== Delete Book ==========\n";

    try
    {
        cout << "Enter book ID to delete: ";
        int bookId = Utilities::readInt(cin, cout);

        Book *book = Book::getPointer(bookId);

        if (!book)
        {
            cout << "Book not found!\n";
            return;
        }

        cout << "Are you sure you want to delete book: " << book->getTitle()
             << " by " << book->getAuthor() << "? (yes/no): ";
        string confirm = Utilities::readString(cin, cout);

        if (confirm == "yes" || confirm == "YES")
        {
            Book::deleteBook(bookId);
            cout << "Book deleted successfully!\n";
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

void Admin::adminUpdateBook()
{
    cout << "\n========== Update Book ==========\n";

    try
    {
        cout << "Enter book Title: ";
        string bookTitle = Utilities::readString(cin, cout);

        Book::updateBookData(bookTitle);
    }
    catch (runtime_error &e)
    {
        cout << e.what() << "\n";
    }
}

void Admin::adminPrintBook()
{
    cout << "\n========== Print Book ==========\n";

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