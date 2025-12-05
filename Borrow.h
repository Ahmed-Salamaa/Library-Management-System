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
    const Date borrowDate;
    Date returnDate;
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

    // Initializes a Borrow object with a predefined ID and custom return date (used during system initialization).
    // @param id: The unique identifier for the borrow record (must be set before system starts).
    // @param UserId: The ID of the user borrowing the book.
    // @param BookId: The ID of the book being borrowed.
    // @param borrowDate: The date when the book was borrowed.
    // @param returnDate: The date when the book should be returned.
    // @param status: The status of the borrow record (true if active, false if completed).
    // @throws runtime_error: If called after the system has started.
    Borrow(int id, int UserId, int BookId, Date borrowDate, Date returnDate, bool status)
        : id(id), UserId(UserId), BookId(BookId), borrowDate(borrowDate), returnDate(returnDate), status(status)
    {
        if (System::systemStarted())
            throw runtime_error("You cant Create a Borrow object with an setted id after system runs");

        BorrowTable.insert(this);
    }

    // Initializes a Borrow object with an auto-generated ID and custom return date (used during runtime).
    // @param UserId: The ID of the user borrowing the book.
    // @param BookId: The ID of the book being borrowed.
    // @param borrowDate: The date when the book was borrowed.
    // @param returnDate: The date when the book should be returned.
    // @param status: The status of the borrow record (true if active, false if completed).
    // @throws runtime_error: If called before the system has started.
    Borrow(int UserId, int BookId, Date borrowDate, Date returnDate, bool status)
        : id(++ID_START), UserId(UserId), BookId(BookId), borrowDate(borrowDate), returnDate(returnDate), status(status)
    {
        if (!System::systemStarted())
            throw runtime_error("You cant Create a Borrow object before system runs");

        BorrowTable.insert(this);
    }

<<<<<<< Updated upstream
    // Initializes a Borrow object with an auto-generated ID and default return date of 3 days (used during runtime).
    // @param UserId: The ID of the user borrowing the book.
    // @param BookId: The ID of the book being borrowed.
    // @param borrowDate: The date when the book was borrowed.
    // @param status: The status of the borrow record (true if active, false if completed).
    // @throws runtime_error: If called before the system has started.
    Borrow(int UserId, int BookId, Date borrowDate, bool status)
        : id(++ID_START), UserId(UserId), BookId(BookId), borrowDate(borrowDate), returnDate(borrowDate + 3), status(status)
    {
        if (!System::systemStarted())
            throw runtime_error("You cant Create a Borrow object before system runs");

        BorrowTable.insert(this);
    }
    Borrow(int UserId, int BookId, bool status)
        : id(++ID_START), UserId(UserId), BookId(BookId), status(status)
    {
        if (!System::systemStarted())
            throw runtime_error("You cant Create a Borrow object before system runs");

        BorrowTable.insert(this);
=======
    friend ostream &operator<<(ostream &out, const Borrow &obj)
    {
        string menuName = "Borrow Info";
        const vector<pair<string, string>> menu =
            {
                {"Book Title", Book::getPointer(obj.BookId)->getTitle()},
                {"User Name", User::getPointer(obj.UserId)->getName()},
                {"Status", to_string(obj.status)}};

        Utilities::printData(menuName, menu, out);

        return out;
>>>>>>> Stashed changes
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

    // Retrieves the borrow date of this record.
    // @return: The Date object representing when the book was borrowed.
    Date getBorrowDate() const { return borrowDate; }

    // Retrieves the return date of this record.
    // @return: The Date object representing when the book should be returned.
    Date getReturnDate() const { return returnDate; }

    // Sets the return date of this record.
    // @param value: The new return date.
    void setReturnDate(Date value) { returnDate = value; }

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

<<<<<<< Updated upstream
    bool hasAbookToReturn(int UserId)
=======
    // Checks if a user has any books that need to be returned.
    // @param UserId: The ID of the user to check.
    // @return: True if the user has at least one active borrow record, false otherwise.
    int bookToReturn(int UserId)
>>>>>>> Stashed changes
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
    // before using this function we need to use hasAbookToReturn if the returned value of the function
    // true we use this function if no then we can not use it
    void changeStatusOfBookForRutern(int BookId)
    {
        vector<Borrow *> historyOfBorrowsForAUser = searchAll(System::currPtr->getId());

        for (auto &&i : historyOfBorrowsForAUser)
        {
            if (i->getBookId() == BookId)
            {
                i->setStatus(false);
                Book::updateBookData(BookId);
                return;
            }
        }
    }
    void changeStatusOfBookForBorrow(int BookId)
    {
        try
        {
            if (Book::isAvailable(BookId))
            {
                Borrow(System::currPtr->getId(), BookId, true);
            }
        }
        catch (runtime_error &e)
        {
            throw runtime_error("The book is not available right now for borrow");
        }
    }

    void returnBook(int userId)
    {

        int bookId = bookToReturn(userId);
        if (bookId == -1)
        {
            throw runtime_error("No active borrowed books found for this user.");
            return;
        }
        else
        {
            changeStatusOfBookForRutern(bookId);
        }
    }
};

#endif