#ifndef FILE_BOOK
#define FILE_BOOK

#include <bits/stdc++.h>
using namespace std;

#include "System.h"
#include "Utilities.h"

class System ;
class Book
{
private:
    static LinkedList<Book *> BookTable;
    static int ID_START;

    const int id;
    int quantity;
    string title;
    string author;

public:
    // Retrieves a pointer to a Book object by its ID.
    // @param id: The ID of the book to search for.
    // @return A pointer to the Book object if found, or nullptr otherwise.
    // @throws runtime_error: If no book with the given ID exists.
    static Book *getPointer(int id)
    {
        function<bool(Book *)> condition = [&](Book *obj)
        {
            return obj->getId() == id;
        };

        return BookTable.search(condition);
    }

    // Retrieves a pointer to a Book object by its title.
    // @param title: The title of the book to search for.
    // @return A pointer to the Book object if found, or nullptr otherwise.
    // @throws runtime_error: If no book with the given title exists.
    static Book *getPointer(string title)
    {
        function<bool(Book *)> condition = [&](Book *obj)
        {
            return obj->getTitle() == title;
        };

        return BookTable.search(condition);
    }

    // Deletes a Book object from the book table using a pointer reference.
    // @param ptr: A pointer to the Book object to delete.
    // @throws runtime_error: If the pointer is invalid (nullptr).
    static void deleteBook(Book *ptr)
    {
        if (!ptr)
            throw runtime_error("Cannot delete Book: Invalid reference");

        function<bool(Book *)> condition = [&](Book *obj)
        {
            return obj == ptr;
        };

        BookTable.erase(condition);
    }

    // Deletes a Book object from the book table using its ID.
    // @param id: The ID of the book to delete.
    // @throws runtime_error: If no book with the given ID exists.
    static void deleteBook(int id)
    {
        Book *ptr = getPointer(id);

        if (ptr)
            deleteBook(ptr);
        else
            throw runtime_error("Cannot delete Book: No Book found with ID " + to_string(id));
    }

    // Initializes a Book object with a predefined ID (used during system initialization).
    // @param id: The unique identifier for the book (must be set before system starts).
    // @param quantity: The number of copies available.
    // @param title: The title of the book.
    // @param author: The author of the book.
    // @throws runtime_error: If called after the system has started.
    Book(int id, int quantity, const string &title, const string &author)
        : id(id), quantity(quantity), title(title), author(author)
    {
        if (System::isSystemStarted())
            throw runtime_error("You cant Create a User with an setted id after system runs");

        BookTable.insert(this);
    }

    // Initializes a Book object with an auto-generated ID (used during runtime).
    // @param quantity: The number of copies available.
    // @param title: The title of the book.
    // @param author: The author of the book.
    // @throws runtime_error: If called before the system has started.
    Book(int quantity, const string &title, const string &author)
        : id(++ID_START), quantity(quantity), title(title), author(author)
    {
        if (!System::isSystemStarted())
            throw runtime_error("You cant Create a User before system runs");

        BookTable.insert(this);
    }

    // Overloads the << operator to output book information in a formatted display.
    // @param out: The output stream to write to.
    // @param obj: The Book object whose data will be displayed.
    // @return The output stream reference for chaining.
    friend ostream &operator<<(ostream &out, const Book &obj)
    {
        string menuName = "Book Info";
        const vector<pair<string, string>> menu =
            {
                {"Quantity", to_string(obj.quantity)},
                {"Title", obj.title},
                {"Author", obj.author}};

        Utilities::printData(menuName, menu, out);

        return out;
    }

    // Retrieves the unique identifier of this book.
    // @return The ID of the book.
    int getId() const { return id; }

    // Retrieves the title of this book.
    // @return The title as a string.
    string getTitle() const { return title; }

    // Sets the title of this book.
    // @param title: The new title for the book.
    void setTitle(const string &title) { this->title = title; }

    // Retrieves the author of this book.
    // @return The author as a string.
    string getAuthor() const { return author; }

    // Sets the author of this book.
    // @param author: The new author for the book.
    void setAuthor(const string &author) { this->author = author; }

    void setQuantity(int quantity) { this->quantity = quantity; }
    int getQuantity() { return this->quantity; }

    // Checks if a book is available for borrowing.
    // @param BookId: The ID of the book to check.
    // @return True if the book exists and has quantity greater than 0, false otherwise.
    static bool isAvailable(int BookId)
    {
        try
        {
            Book *book = getPointer(BookId);
            return book->getQuantity() > 0;
        }
        catch (runtime_error &e)
        {
            return false;
        }
    }

    static void updateBookData(int BookId)
    {
        auto bookPtr = getPointer(BookId);

        if (!bookPtr)
        {
            throw runtime_error("Book not found!");
            return;
        }

        string menuName = "Which data do you want to update?";
        vector<string> menu =
            {
                "Title",
                "Author",
                "Quantity",
            };

        try
        {
            int choice = Utilities::printMenu(menuName, menu);

            if (choice == 1)
            {
                cout << "Enter new title: ";
                string newTitle = Utilities::readString();
                bookPtr->setTitle(newTitle);
            }
            else if (choice == 2)
            {
                cout << "Enter new author: ";
                string newAuthor = Utilities::readString();
                bookPtr->setAuthor(newAuthor);
            }
            else if (choice == 3)
            {
                cout << "Enter new quantity: ";
                int newQuantity = Utilities::readInt(0, 1e9);

                bookPtr->setQuantity(newQuantity);
            }
            else
            {
                cout << "Invalid choice!" << endl;
            }
        }
        catch (...)
        {
            return;
        }
    }

    static void increaseQuantity(int BookId)
    {
        auto bookPtr = getPointer(BookId);
        bookPtr->setQuantity(bookPtr->getQuantity() + 1);
    }

    static void decreaseQuantity(int BookId)
    {
        auto bookPtr = getPointer(BookId);
        if (bookPtr->getQuantity() > 0)
        {
            bookPtr->setQuantity(bookPtr->getQuantity() - 1);
        }
        else
        {
            throw runtime_error("Cannot decrease quantity below zero.");
        }
    }

    static vector<Book *> getAll()
    {
        return BookTable.searchAllByPredicate([](Book *obj)
                                              { return true; });
    }

    static void addBook(const string &name, const string &author, int quantity)
    {
        if (quantity <= 0)
        {
            throw runtime_error("Quantity must be >= 1\n");
            return;
        }

        try
        {
            Book *existing = nullptr;
            try
            {
                existing = getPointer(name);
            }
            catch (...)
            {
                existing = nullptr;
            }

            if (existing)
            {
                for (int i = 0; i < quantity; ++i)
                {
                    increaseQuantity(existing->getId());
                }
                return;
            }

            Book(quantity, name, author);
        }
        catch (const exception &e)
        {
            throw runtime_error("Failed to add the book");
        }
    }

    static void printAllBooks()
    {
        try
        {
            vector<Book *> all = Book::getAll();
            if (all.empty())
            {
                throw runtime_error("No books in catalog");
            }

            for (auto b : all)
            {
                cout << *b << "\n";
            }
        }
        catch (const exception &e)
        {
            throw runtime_error("Failed to retrieve books");
        }
    }

    static void viewBooks(string author)
    {
        function<bool(Book*)> condition = [&](Book* obj)
        {
            return obj->getAuthor() == author;
        };

        auto books = BookTable.searchAllByPredicate(condition);

        if (books.empty())
        {
            cout << "No books found for author: " << author << "\n";
            return;
        }

        cout << "\n--- Books by Author: " << author << " ---\n";
        for (auto b : books)
            cout << *b;
    }

    void PrintBookByName()
    {
        string name;
        cout << "Enter Book Name: ";

        try
        {
            name = Utilities::readString() ;
        }
        catch (...)
        {
            return ; // if user refuses to give input return
        }
        
        function<bool(Book*)> condition = [&](Book* obj)
        {
            return obj->getTitle() == name;
        };

        Book* p = BookTable.search(condition);

        if (!p)
            cout << "Book not found.\n";
        else
            cout << *p;     // prints full book info
    }
};

#endif
