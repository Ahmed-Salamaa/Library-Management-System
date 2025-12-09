#ifndef FILE_USER
#define FILE_USER

#include <bits/stdc++.h>
using namespace std;

#include "LinkedList.h"
#include "Utilities.h"
#include "System.h"

class System;
class User
{
private:
    static LinkedList<User *> UserTable;
    static int ID_START;

protected:
    const int id;
    // type = 1 for Student
    // type = 2 for Admin
    int type;
    string name;
    const string username;
    string password;

public:
    // Retrieves a pointer to a User object by its ID.
    // @param id: The ID of the user to search for.
    // @return A pointer to the User object if found, or nullptr otherwise.
    // @throws runtime_error: If no user with the given ID exists.
    static User *getPointer(int id)
    {
        function<bool(User *)> condition = [&](User *obj)
        {
            return obj->getId() == id;
        };

        return UserTable.search(condition);
    }

    // Retrieves a pointer to a User object by their username.
    // @param Username: The username to search for.
    // @return A pointer to the User object if found, or nullptr otherwise.
    // @throws runtime_error: If no user with the given username exists.
    static User *getPointer(string Username)
    {
        function<bool(User *)> condition = [&](User *obj)
        {
            return obj->getUsername() == Username;
        };

        return UserTable.search(condition);
    }

    // Deletes a User object from the user table using a pointer reference.
    // @param ptr: A pointer to the User object to delete.
    // @throws runtime_error: If the pointer is invalid (nullptr).
    static void deleteUser(User *ptr)
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
    // @param id: The ID of the user to delete.
    // @throws runtime_error: If no user with the given ID exists.
    static void deleteUser(int id)
    {
        User *ptr = getPointer(id);

        if (ptr)
            deleteUser(ptr);
        else
            throw runtime_error("Cannot delete user: No user found with ID " + to_string(id));
    }

    // Initializes a User object with a predefined ID (used during system initialization).
    // @param id: The unique identifier for the user (must be set before system starts).
    // @param type: The type of user (1 for Student, 2 for Admin).
    // @param name: The full name of the user.
    // @param username: The login username of the user.
    // @param password: The password for authentication.
    // @throws runtime_error: If called after the system has started.
    User(int id, int type, string name, string username, string password)
        : id(id), type(type), name(name), username(username), password(password)
    {
        if (System::isSystemStarted())
            throw runtime_error("You cant Create a User with an setted id after system runs");

        UserTable.insert(this);
    }

    // Initializes a User object with an auto-generated ID (used during runtime).
    // @param type: The type of user (1 for Student, 2 for Admin).
    // @param name: The full name of the user.
    // @param username: The login username of the user.
    // @param password: The password for authentication.
    // @throws runtime_error: If called before the system has started.
    User(int type, string name, string username, string password)
        : id(++ID_START), type(type), name(name), username(username), password(password)
    {
        if (!System::isSystemStarted())
            throw runtime_error("You cant Create a User before system runs");

        UserTable.insert(this);
    }

    virtual ~User() {}

    // Overloads the << operator to output user profile information in a formatted display.
    // @param out: The output stream to write to.
    // @param obj: The User object whose profile will be displayed.
    // @return The output stream reference for chaining.
    friend ostream &operator<<(ostream &out, const User &obj)
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
    // @return The ID of the user.
    int getId() const { return id; }

    string getPassword() const { return password; }

    // Retrieves the full name of this user.
    // @return The name as a string.
    string getName() const { return name; }

    // Sets the name of this user.
    // @param value: The new name for the user.
    void setName(string value) { name = value; }

    // Retrieves the login username of this user.
    // @return The username as a string.
    string getUsername() const { return username; }

    // Retrieves the type of this user.
    // @return The user type (1 for Student, 2 for Admin).
    int getType() const { return type; }

    // Sets the type of this user.
    // @param value: The new user type (1 for Student, 2 for Admin).
    void setType(int value) { type = value; }

    // Displays the main menu for the user.
    // This is a virtual method to be overridden by subclasses (Student, Admin).
    virtual void mainMenu(){

    }

    // Displays the user account management menu.
    // Provides options for viewing profile, changing password, and logging out.
    void userMenu()
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

    static void addUser()
    {
        try
        {
            cout << "\n========== Add New User ==========\n";

            string typeMenu = "Select User Type";
            vector<string> typeOptions = {"Student", "Admin"};
            int typeChoice = Utilities::printMenu(typeMenu, typeOptions, cout);

            int type = Utilities::readInt(1, 2);
            string name = Utilities::readString();
            string username = Utilities::readUsername();
            string password = Utilities::readPassword();
            User *exist = getPointer(username);
            if (exist != NULL)
            {
                throw runtime_error("Username already exists.");
            }
            User(type, name, username, password);
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

    static void updateUserPassword(int id)
    {
        User *ptr = getPointer(id);
        if (!ptr)
        {
            throw runtime_error("User not found.");
        }
        Utilities::setPassword(ptr->password);
    }
    void changeCurrentUserPassword()
    {
        User *ptr = System::currPtr;
        if (!ptr)
        {
            throw runtime_error("User not found.");
        }
        Utilities::setPassword(ptr->password);
    }

    static void printUser(int Id)
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

    static void PrintAllUsers()
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
};

#endif