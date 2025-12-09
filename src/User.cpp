#include <bits/stdc++.h>
using namespace std;

#include "../include/LinkedList.h"
#include "../include/Utilities.h"
#include "../include/System.h"
#include "../include/User.h"
#include "../include/Student.h"
#include "../include/Admin.h"

// Static member definitions
LinkedList<User *> User::UserTable;
int User::ID_START = 1000000;


// Retrieves a pointer to a User object by its ID.
User *User::getPointer(int id)
{
    function<bool(User *)> condition = [&](User *obj)
    {
        return obj->getId() == id;
    };

    return UserTable.search(condition);
}

// Retrieves a pointer to a User object by their username.
User *User::getPointer(string Username)
{
    function<bool(User *)> condition = [&](User *obj)
    {
        return obj->getUsername() == Username;
    };

    return UserTable.search(condition);
}

// Deletes a User object from the user table using a pointer reference.
void User::deleteUser(User *ptr)
{
    if (!ptr)
        throw runtime_error("Cannot delete User: Invalid reference");

    function<bool(User *)> condition = [&](User *obj)
    {
        return obj == ptr;
    };

    UserTable.erase(condition);
}

// Deletes a User object from the user table using their ID.
void User::deleteUser(int id)
{
    User *ptr = getPointer(id);

    if (ptr)
        deleteUser(ptr);
    else
        throw runtime_error("Cannot delete user: No user found with ID " + to_string(id));
}

// Initializes a User object with a predefined ID (used during system initialization).
User::User(int id, int type, string name, string username, string password)
    : id(id), type(type), name(name), username(username), password(password)
{
    if (System::isSystemStarted())
        throw runtime_error("You cant Create a User with an setted id after system runs");

    UserTable.insert(this);
}

// Initializes a User object with an auto-generated ID (used during runtime).
User::User(int type, string name, string username, string password)
    : id(++ID_START), type(type), name(name), username(username), password(password)
{
    if (!System::isSystemStarted())
        throw runtime_error("You cant Create a User before system runs");

    UserTable.insert(this);
}

User::~User() {}

// Overloads the << operator to output user profile information in a formatted display.
ostream &operator<<(ostream &out, const User &obj)
{
    string menuName = "User Profile";
    const vector<pair<string, string>> menu =
        {
            {"Name", obj.name},
            {"Username", obj.username},
            {"Type", (obj.type == 1 ? "Student" : "Admin")}};

    Utilities::printData(menuName, menu, out);

    return out;
}

// Retrieves the unique identifier of this user.
int User::getId() { return id; }

string User::getPassword() { return password; }

// Retrieves the full name of this user.
string User::getName() { return name; }

// Sets the name of this user.
void User::setName(string value) { name = value; }

// Retrieves the login username of this user.
string User::getUsername() { return username; }

// Retrieves the type of this user.
int User::getType() { return type; }

// Sets the type of this user.
void User::setType(int value) { type = value; }

// Displays the user account management menu.
void User::userMenu()
{
    string menuName = "User Account Menu";
    const vector<string> menu =
        {
            "View Profile",
            "Change Password",
            "Change Name",
            "Logout"};

    int chose = Utilities::printMenu(menuName, menu, cout);
    int idx = 1;

    if (chose == idx++)
    {
        cout << *this;
    }
    else if (chose == idx++)
    {
        // will add later
    }
    else if (chose == idx++)
    {
        // will add later
    }
    else if (chose == idx++)
    {
        // will add later
    }
    else
    {
        throw runtime_error("Invaild option");
    }
}

void User::updateUserPassword(int id)
{
    User *ptr = getPointer(id);
    if (!ptr)
    {
        throw runtime_error("User not found.");
    }
    Utilities::setPassword(ptr->password);
}

void User::printUser(int Id)
{
    try
    {
        User *p = User::getPointer(Id);
        cout << *p;
    }
    catch (...)
    {
        cout << "Error: User with ID " << Id << " doesn't exist!" << endl;
    }
}

void User::PrintAllUsers()
{
    function<bool(User *)> condation = [&](User *obj)
    {
        return 1;
    };

    auto usersPointers = UserTable.searchAllByPredicate(condation);

    if (usersPointers.empty())
    {
        cout << "No users in the system." << endl;
    }
    else
    {
        for (auto it : usersPointers)
        {
            cout << *it;
        }
    }
}

void User::addUser()
{
    try
    {
        cout << "\n========== Add New User ==========\n";

        string typeMenu = "Select User Type";
        vector<string> typeOptions = {"Student", "Admin"};
        int typeChoice = Utilities::printMenu(typeMenu, typeOptions, cout);

        cout << "Enter name: ";
        string name = Utilities::readString();
        cout << "Enter username: ";
        string username = Utilities::readUsername();
        
        User *exist = nullptr;
        try {
            exist = getPointer(username);
        } catch (...) {
            exist = nullptr;
        }
        
        if (exist != nullptr)
        {
            throw runtime_error("Username already exists.");
        }
        
        cout << "Enter password: ";
        string password = Utilities::readPassword();

        if (typeChoice == 1)
            new Student(name, username, password);
        else
            new Admin(name, username, password);

        cout << "User added successfully!\n";
    }
    catch (const runtime_error &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
    catch (...)
    {
        cout << "Unknown error occurred while adding user." << endl;
    }
}

void User::changeCurrentUserPassword()
{
    User *ptr = System::currPtr;
    if (!ptr)
    {
        throw runtime_error("User not found.");
    }
    Utilities::setPassword(ptr->password);
}