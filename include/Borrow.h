#ifndef FILE_BORROW
#define FILE_BORROW

#include <bits/stdc++.h>
using namespace std;

#include "System.h"
#include "Book.h"
#include "User.h"

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
    // @return A pointer to the Borrow object if found, or nullptr otherwise.
    // @throws runtime_error: If no borrow record with the given ID exists.
    static Borrow *getPointer(int id) ;

    // Initializes a Borrow object with a predefined ID (used during system initialization).
    // @param id: The unique identifier for the borrow record (must be set before system starts).
    // @param UserId: The ID of the user borrowing the book.
    // @param BookId: The ID of the book being borrowed.
    // @param status: The status of the borrow record (true if active, false if completed).
    // @throws runtime_error: If called after the system has started.
    Borrow(int id, int UserId, int BookId, bool status) ;

    // Initializes a Borrow object with an auto-generated ID (used during runtime).
    // @param UserId: The ID of the user borrowing the book.
    // @param BookId: The ID of the book being borrowed.
    // @param status: The status of the borrow record (true if active, false if completed).
    // @throws runtime_error: If called before the system has started.
    Borrow(int UserId, int BookId, bool status) ;

    // Overloads the << operator to output borrow information in a formatted display.
    // @param out: The output stream to write to.
    // @param obj: The Borrow object whose data will be displayed.
    // @return The output stream reference for chaining.
    friend ostream &operator<<(ostream &out, const Borrow &obj) ;

    // Retrieves the unique identifier of this borrow record.
    // @return The ID of the borrow record.
    int getId() ;

    // Retrieves the ID of the user associated with this borrow record.
    // @return The user ID.
    int getUserId() ;

    // Retrieves the ID of the book associated with this borrow record.
    // @return The book ID.
    int getBookId() ;

    // Retrieves the status of this borrow record.
    // @return True if the record is active, false if completed.
    bool getStatus() ;

    // Sets the status of this borrow record.
    // @param value: The new status (true for active, false for completed).
    void setStatus(bool value) ;

    // Searches for all borrow records associated with a specific user.
    // @param UserId: The ID of the user whose borrow records to retrieve.
    // @return A vector containing pointers to all Borrow objects for the user.
    static vector<Borrow *> searchAll(int UserId) ;

    // Checks if a user has any books that need to be returned.
    // @param UserId: The ID of the user to check (currently unused, uses System::currPtr instead).
    // @return True if the user has at least one active borrow record, false otherwise.
    static bool hasAbookToReturn(int UserId) ;

    // @param UserId: The ID of the user to check.
    // @return: bookId if the user has at least one active borrow record, -1 otherwise.
    static int bookToReturn() ;

    // Changes the status of a book borrow record to returned (false).
    // Note: Before using this function, call hasAbookToReturn() to verify the user has books to return.
    // @param BookId: The ID of the book being returned.
    static void changeStatusOfBookForRutern(int BookId) ;

    // Creates a new borrow record for the current user if the book is available.
    // @param BookId: The ID of the book to borrow.
    // @throws runtime_error: If the book is not available for borrowing.
    static void changeStatusOfBookForBorrow(int BookId) ;

    static void borrowBook(int userId, const string &bookName) ;

    static void GetHistoryByUser() ;
    
};

#endif