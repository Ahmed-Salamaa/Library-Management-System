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
         // Displays the main menu for an admin.
    // Overrides the virtual method from the User class.
    void mainMenu() override
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

private:

private:
    static void adminAddUser()
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
                cout << "✓ Student created successfully!\n";
            }
            else
            {
                newUser = new Admin(name, username, password);
                cout << "✓ Admin created successfully!\n";
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

    // 2. Updates the password of a user by their ID.
    static void adminUpdateUserPassword()
    {
        cout << "\n========== Update User Password ==========\n";

        try
        {
            cout << "Enter user ID: ";
            int userId = Utilities::readInt(cin, cout);

            User::updateUserPassword(userId);
        }
        catch (runtime_error &e)
        {
            cout << "Error: " << e.what() << "\n";
        }
    }

    // Deletes a user from the system by their ID.
    static void adminDeleteUser()
    {
        cout << "\n========== Delete User ==========\n";

        try
        {
            cout << "Enter user ID to delete: ";
            int userId = Utilities::readInt(cin, cout);

            User *user = User::getPointer(userId);

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
                User::deleteUser(userId);
                cout << "✓ User deleted successfully!\n";
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

    //  Searches for and displays a user by their ID.
    static void adminPrintUser()
    {
        cout << "\n========== Print User ==========\n";

        try
        {
            cout << "Enter user ID: ";
            int userId = Utilities::readInt(cin, cout);

            User::printUser(userId);
        }
        catch (runtime_error &e)
        {
            cout << "Error: " << e.what() << "\n";
        }
    }

    // Adds a new book to the library system.
    static void adminAddBook()
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
            cout << "✓ Book added successfully!\n";
        }
        catch (runtime_error &e)
        {
            cout << "Error: " << e.what() << "\n";
        }
    }
    // Deletes a book from the library system by its ID.
    static void adminDeleteBook()
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
                cout << "✓ Book deleted successfully!\n";
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

    // Updates book information (title, author, or quantity).
    static void adminUpdateBook()
    {
        cout << "\n========== Update Book ==========\n";

        try
        {
            cout << "Enter book Title: ";
            string  bookTitle = Utilities::readString(cin, cout);

            Book::updateBookData(bookTitle);
        }
        catch (runtime_error &e)
        {
            cout << e.what() << "\n";
        }
    }

    // Searches for and displays a book by its title.
    static void adminPrintBook()
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
} ;

#endif