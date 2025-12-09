#include <bits/stdc++.h>
using namespace std;

#include "../include/LinkedList.h"
#include "../include/Utilities.h"
#include "../include/System.h"
#include "../include/Book.h"

// Static member definitions
LinkedList<Book *> Book::BookTable;
int Book::ID_START = 2000000;

Book *Book::getPointer(int id)
{
    function<bool(Book *)> condition = [&](Book *obj)
    {
        return obj->getId() == id;
    };

    return BookTable.search(condition);
}

Book *Book::getPointer(string title)
{
    function<bool(Book *)> condition = [&](Book *obj)
    {
        return obj->getTitle() == title;
    };

    return BookTable.search(condition);
}

void Book::deleteBook(Book *ptr)
{
    if (!ptr)
        throw runtime_error("Cannot delete Book: Invalid reference");

    function<bool(Book *)> condition = [&](Book *obj)
    {
        return obj == ptr;
    };

    BookTable.erase(condition);
}

void Book::deleteBook(int id)
{
    Book *ptr = getPointer(id);

    if (ptr)
        deleteBook(ptr);
    else
        throw runtime_error("Cannot delete Book: No Book found with ID " + to_string(id));
}

Book::Book(int id, int quantity, const string &title, const string &author)
    : id(id), quantity(quantity), title(title), author(author)
{
    if (System::isSystemStarted())
        throw runtime_error("You cant Create a Book with an setted id after system runs");

    BookTable.insert(this);
}

Book::Book(int quantity, const string &title, const string &author)
    : id(++ID_START), quantity(quantity), title(title), author(author)
{
    if (!System::isSystemStarted())
        throw runtime_error("You cant Create a Book before system runs");

    BookTable.insert(this);
}

ostream &operator<<(ostream &out, const Book &obj)
{
    string menuName = "Book Info";
    const vector<pair<string, string>> menu =
        {
            {"Title", obj.title},
            {"Author", obj.author},
            {"Quantity", to_string(obj.quantity)}
        };

    Utilities::printData(menuName, menu, out);

    return out;
}

int Book::getId() { return id; }

string Book::getTitle() { return title; }

void Book::setTitle(const string &title) { this->title = title; }

string Book::getAuthor() { return author; }

void Book::setAuthor(const string &author) { this->author = author; }

void Book::setQuantity(int quantity) { this->quantity = quantity; }

int Book::getQuantity() { return this->quantity; }

bool Book::isAvailable(int BookId)
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

void Book::updateBookData(string BookTitle)
{
    auto bookPtr = getPointer(BookTitle);

    if (!bookPtr)
    {
        throw runtime_error("Book not found!");
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

void Book::increaseQuantity(int BookId)
{
    auto bookPtr = getPointer(BookId);
    bookPtr->setQuantity(bookPtr->getQuantity() + 1);
}

void Book::decreaseQuantity(int BookId)
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

vector<Book *> Book::getAll()
{
    return BookTable.searchAllByPredicate([](Book *obj)
                                          { return true; });
}

void Book::addBook(const string &name, const string &author, int quantity)
{
    if (quantity <= 0)
    {
        throw runtime_error("Quantity must be >= 1\n");
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

        new Book(quantity, name, author);
    }
    catch (const exception &e)
    {
        throw runtime_error("Failed to add the book");
    }
}

void Book::printAllBooks()
{
    vector<Book *> all;

    try
    {
        all = Book::getAll();
    }
    catch (...)
    {
        cout << "Error: Could not read book list.\n";
        return;
    }

    if (all.empty())
    {
        cout << "No books in catalog.\n";
        return;
    }

    for (auto b : all)
    {
        if (b)
            cout << *b << "\n";
        else
            cout << "Error: Invalid book entry.\n";
    }
}

void Book::viewBooks(string author)
{
    function<bool(Book *)> condition = [&](Book *obj)
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

void Book::PrintBookByName()
{
    string name;
    cout << "Enter Book Name: ";

    try
    {
        name = Utilities::readString();
    }
    catch (...)
    {
        return;
    }

    function<bool(Book *)> condition = [&](Book *obj)
    {
        return obj->getTitle() == name;
    };

    Book *p = BookTable.search(condition);

    if (!p)
        cout << "Book not found.\n";
    else
        cout << *p;
}
