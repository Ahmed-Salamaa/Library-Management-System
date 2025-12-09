#include <bits/stdc++.h>
using namespace std;

#include "../include/LinkedList.h"
#include "../include/Utilities.h"
#include "../include/System.h"
#include "../include/User.h"
#include "../include/Book.h"
#include "../include/Borrow.h"

// Static member definitions
LinkedList<Borrow *> Borrow::BorrowTable;
int Borrow::ID_START = 3000000;

Borrow *Borrow::getPointer(int id)
{
    function<bool(Borrow *)> condition = [&](Borrow *obj)
    {
        return obj->getId() == id;
    };

    return BorrowTable.search(condition);
}

Borrow::Borrow(int id, int UserId, int BookId, bool status)
    : id(id), UserId(UserId), BookId(BookId), status(status)
{
    if (System::isSystemStarted())
        throw runtime_error("You cant Create a Borrow object with an setted id after system runs");

    BorrowTable.insert(this);
}

Borrow::Borrow(int UserId, int BookId, bool status)
    : id(++ID_START), UserId(UserId), BookId(BookId), status(status)
{
    if (!System::isSystemStarted())
        throw runtime_error("You cant Create a Borrow object before system runs");

    BorrowTable.insert(this);
}

ostream &operator<<(ostream &out, const Borrow &obj)
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

int Borrow::getId() { return id; }

int Borrow::getUserId() { return UserId; }

int Borrow::getBookId() { return BookId; }

bool Borrow::getStatus() { return status; }

void Borrow::setStatus(bool value) { status = value; }

vector<Borrow *> Borrow::searchAll(int UserId)
{
    function<bool(Borrow *)> condition = [&](Borrow *obj)
    {
        return obj->getUserId() == UserId;
    };

    return BorrowTable.searchAllByPredicate(condition);
}

bool Borrow::hasAbookToReturn(int UserId)
{
    vector<Borrow *> historyOfBorrowsForAUser = searchAll(UserId);
    bool hasAbook = false;
    for (auto &i : historyOfBorrowsForAUser)
    {
        if (i->getStatus() == true)
        {
            hasAbook = true;
            break;
        }
    }
    return hasAbook;
}

int Borrow::bookToReturn()
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

void Borrow::changeStatusOfBookForRutern(int BookId)
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

void Borrow::changeStatusOfBookForBorrow(int BookId)
{
    try
    {
        if (Book::isAvailable(BookId))
        {
            new Borrow(System::currPtr->getId(), BookId, true);
            Book::decreaseQuantity(BookId);
        }
    }
    catch (runtime_error &e)
    {
        throw runtime_error("The book is not available right now for borrow");
    }
}

void Borrow::borrowBook(int userId, const string &bookName)
{
    User *prev = System::currPtr;
    try
    {
        User *u = User::getPointer(userId);
        if (!u)
        {
            throw runtime_error("User not found");
        }

        System::currPtr = u;

        Book *b = nullptr;
        try
        {
            b = Book::getPointer(bookName);
        }
        catch (...)
        {
            b = nullptr;
        }

        if (!b)
        {
            throw runtime_error("Book not found");
        }
        changeStatusOfBookForBorrow(b->getId());
    }
    catch (const exception &e)
    {
        throw runtime_error(e.what());
    }
}

void Borrow::GetHistoryByUser()
{
    int uid = System::currPtr->getId();

    function<bool(Borrow *)> condition = [&](Borrow *obj)
    {
        return obj->getUserId() == uid;
    };

    auto records = BorrowTable.searchAllByPredicate(condition);

    if (records.empty())
    {
        cout << "No borrowing history for this user.\n";
        return;
    }

    cout << "\n--- Borrow History for User " << uid << " ---\n";

    for (auto r : records)
        cout << *r;
}
