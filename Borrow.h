#ifndef FILE_BORROW
#define FILE_BORROW

#include <bits/stdc++.h>
using namespace std;

#include "System.h"
#include "Book.h"

class Borrow
{
private:
    static LinkedList<Borrow *> BorrowTable;
    static int ID_START;

    const int id;
    const int UserId;
    const int BookId;
    bool status;

public:
    // Retrieves a pointer to a Borrow object by its ID.
    // @param id: The ID of the borrow record to search for.
    // @return: A pointer to the Borrow object if found, or nullptr otherwise.
    // @throws runtime_error: If no borrow record with the given ID exists.
    static Borrow *getPointer(int id)
    {
        function<bool(Borrow *)> condition = [&](Borrow *obj)
        {
            return obj->getId() == id;
        };

        return BorrowTable.search(condition);
    }

    // Initializes a Borrow object with a predefined ID (used during system initialization).
    // @param id: The unique identifier for the borrow record (must be set before system starts).
    // @param UserId: The ID of the user borrowing the book.
    // @param BookId: The ID of the book being borrowed.
    // @param status: The status of the borrow record (true if active, false if completed).
    // @throws runtime_error: If called after the system has started.
    Borrow(int id, int UserId, int BookId, bool status)
        : id(id), UserId(UserId), BookId(BookId), status(status)
    {
        if (System::systemStarted())
            throw runtime_error("You cant Create a Borrow object with an setted id after system runs");

        BorrowTable.insert(this);
    }

    // Initializes a Borrow object with an auto-generated ID (used during runtime).
    // @param UserId: The ID of the user borrowing the book.
    // @param BookId: The ID of the book being borrowed.
    // @param status: The status of the borrow record (true if active, false if completed).
    // @throws runtime_error: If called before the system has started.
    Borrow(int UserId, int BookId, bool status)
        : id(++ID_START), UserId(UserId), BookId(BookId), status(status)
    {
        if (!System::systemStarted())
            throw runtime_error("You cant Create a Borrow object before system runs");

        BorrowTable.insert(this);
    }

    friend ostream &operator<< (ostream &out, const Borrow &obj)
    {
        string menuName = "Borrow Info";
        const vector<pair<string, string>> menu =
            {
                {"Book Title", Book::getPointer(obj.BookId)->getTitle()},
                {"User Name", User::getPointer(obj.UserId)->getName()},
                {"Status", to_string(obj.status)}};

        Utilities::printData(menuName, menu, out);

        return out;
    }

    // Retrieves the unique identifier of this borrow record.
    // @return: The ID of the borrow record.
    int getId() const { return id; }

    // Retrieves the ID of the user associated with this borrow record.
    // @return: The user ID.
    int getUserId() const { return UserId; }

    // Retrieves the ID of the book associated with this borrow record.
    // @return: The book ID.
    int getBookId() const { return BookId; }

    // Retrieves the status of this borrow record.
    // @return: True if the record is active, false if completed.
    bool getStatus() const { return status; }

    // Sets the status of this borrow record.
    // @param value: The new status (true for active, false for completed).
    void setStatus(bool value) { status = value; }

    // Searches for all borrow records associated with a specific user.
    // @param UserId: The ID of the user whose borrow records to retrieve.
    // @return: A vector containing pointers to all Borrow objects for the user.
    static vector<Borrow *> searchAll(int UserId)
    {
        function<bool(Borrow *)> condition = [&](Borrow *obj)
        {
            return obj->getUserId() == UserId;
        };

        return BorrowTable.searchAllByPredicate(condition);
    }

    // Checks if a user has any books that need to be returned.
    // @param UserId: The ID of the user to check (currently unused, uses System::currPtr instead).
    // @return: True if the user has at least one active borrow record, false otherwise.
    bool hasAbookToReturn(int UserId)
      
    // @param UserId: The ID of the user to check.
    // @return: bookId if the user has at least one active borrow record, -1 otherwise.
    int bookToReturn(int UserId)
    {
        vector<Borrow *> historyOfBorrowsForAUser = searchAll(System::currPtr->getId());
        int bookId = -1;
        for (auto &&i : historyOfBorrowsForAUser)
        {
            if (i->getStatus() == true)
            {
                bookId = i->getBookId();
                break;
            }
        }
        return bookId;
    }

    // Changes the status of a book borrow record to returned (false).
    // Note: Before using this function, call hasAbookToReturn() to verify the user has books to return.
    // @param BookId: The ID of the book being returned.
    void changeStatusOfBookForRutern(int BookId)
    {
        vector<Borrow *> historyOfBorrowsForAUser = searchAll(System::currPtr->getId());

        for (auto &&i : historyOfBorrowsForAUser)
        {
            if (i->getBookId() == BookId)
            {
                i->setStatus(false);
                Book::increaseQuantity(BookId);
                return;
            }
        }
    }

    // Creates a new borrow record for the current user if the book is available.
    // @param BookId: The ID of the book to borrow.
    // @throws runtime_error: If the book is not available for borrowing.
    void changeStatusOfBookForBorrow(int BookId)
    {
        try
        {
            if (Book::isAvailable(BookId))
            {
                Borrow(System::currPtr->getId(), BookId, true);
                Book::decreaseQuantity(BookId);
            }
        }
        catch (runtime_error &e)
        {
            throw runtime_error("The book is not available right now for borrow");
        }
    }
};

#endif