#ifndef FILE_BOOK
#define FILE_BOOK

#include <bits/stdc++.h>
using namespace std;

#include "System.h"
#include "Utilities.h"

class System;
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
    static Book *getPointer(int id) ;

    // Retrieves a pointer to a Book object by its title.
    // @param title: The title of the book to search for.
    // @return A pointer to the Book object if found, or nullptr otherwise.
    // @throws runtime_error: If no book with the given title exists.
    static Book *getPointer(string title) ;

    // Deletes a Book object from the book table using a pointer reference.
    // @param ptr: A pointer to the Book object to delete.
    // @throws runtime_error: If the pointer is invalid (nullptr).
    static void deleteBook(Book *ptr) ;

    // Deletes a Book object from the book table using its ID.
    // @param id: The ID of the book to delete.
    // @throws runtime_error: If no book with the given ID exists.
    static void deleteBook(int id) ;

    // Initializes a Book object with a predefined ID (used during system initialization).
    // @param id: The unique identifier for the book (must be set before system starts).
    // @param quantity: The number of copies available.
    // @param title: The title of the book.
    // @param author: The author of the book.
    // @throws runtime_error: If called after the system has started.
    Book(int id, int quantity, const string &title, const string &author) ;

    // Initializes a Book object with an auto-generated ID (used during runtime).
    // @param quantity: The number of copies available.
    // @param title: The title of the book.
    // @param author: The author of the book.
    // @throws runtime_error: If called before the system has started.
    Book(int quantity, const string &title, const string &author) ;

    // Overloads the << operator to output book information in a formatted display.
    // @param out: The output stream to write to.
    // @param obj: The Book object whose data will be displayed.
    // @return The output stream reference for chaining.
    friend ostream &operator<<(ostream &out, const Book &obj) ;

    // Retrieves the unique identifier of this book.
    // @return The ID of the book.
    int getId() ;

    // Retrieves the title of this book.
    // @return The title as a string.
    string getTitle() ;

    // Sets the title of this book.
    // @param title: The new title for the book.
    void setTitle(const string &title) ;

    // Retrieves the author of this book.
    // @return The author as a string.
    string getAuthor() ;

    // Sets the author of this book.
    // @param author: The new author for the book.
    void setAuthor(const string &author) ;

    void setQuantity(int quantity) ;

    int getQuantity() ;

    // Checks if a book is available for borrowing.
    // @param BookId: The ID of the book to check.
    // @return True if the book exists and has quantity greater than 0, false otherwise.
    static bool isAvailable(int BookId) ;

    static void updateBookData(string BookTitle) ;

    static void increaseQuantity(int BookId) ;

    static void decreaseQuantity(int BookId) ;

    static vector<Book *> getAll() ;

    static void addBook(const string &name, const string &author, int quantity) ;

    static void printAllBooks() ;

    static void viewBooks(string author) ;

    void PrintBookByName() ;
};

#endif
