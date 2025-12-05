#ifndef FILE_USER
#define FILE_USER

#include <bits/stdc++.h>
using namespace std;

#include "System.h"
#include "Utilities.h"

class User
{
    private:

        static LinkedList < User * > UserTable ;
        static int ID_START ;

    protected:

        const int id;
        string name , password ;
        const string username ;

        // type = 1 for Student
        // type = 2 for Admin
        int type;

    public:

        // Retrieves a pointer to a User object by its ID.
        // @param id: The ID of the user to search for.
        // @return: A pointer to the User object if found, or nullptr otherwise.
        // @throws runtime_error: If no user with the given ID exists.
        static User *getPointer(int id)
        {
            function < bool( User * ) > condition = [&] ( User * obj )
            {
                return obj->getId() == id ;
            };
            
            return UserTable.search( condition );
        }

        // Retrieves a pointer to a User object by their username.
        // @param Username: The username to search for.
        // @return: A pointer to the User object if found, or nullptr otherwise.
        // @throws runtime_error: If no user with the given username exists.
        static User *getPointer( string Username )
        {
            function < bool( User * ) > condition = [&] ( User * obj )
            {
                return obj->getUsername() == Username ;
            };
            
            return UserTable.search( condition );
        }

        // Deletes a User object from the user table using a pointer reference.
        // @param ptr: A pointer to the User object to delete.
        // @throws runtime_error: If the pointer is invalid (nullptr).
        static void deleteUser ( User * ptr )
        {
            if ( !ptr ) throw runtime_error( "Cannot delete User: Invalid reference") ;

            function < bool( User * ) > condition = [&] ( User * obj )
            {
                return obj == ptr ;
            };

            UserTable.erase( condition ) ;
        }

        // Deletes a User object from the user table using their ID.
        // @param id: The ID of the user to delete.
        // @throws runtime_error: If no user with the given ID exists.
        static void deleteUser ( int id )
        {
            User * ptr = getPointer(id);

            if ( ptr ) deleteUser( ptr ) ;
            else throw runtime_error( "Cannot delete user: No user found with ID " + to_string(id) ) ;
        }

        // Initializes a User object with a predefined ID (used during system initialization).
        // @param id: The unique identifier for the user (must be set before system starts).
        // @param type: The type of user (1 for Student, 2 for Admin).
        // @param name: The full name of the user.
        // @param username: The login username of the user.
        // @param password: The password for authentication.
        // @throws runtime_error: If called after the system has started.
        User ( int id , int type , string name , string username , string password )
            : id ( id ) , type ( type ) , name ( name ) , username ( username ) , password ( password ) 
        {
            if ( System::systemStarted() )
                throw runtime_error( "You cant Create a User with an setted id after system runs" ) ;

            UserTable.insert( this ) ;
        }

        // Initializes a User object with an auto-generated ID (used during runtime).
        // @param type: The type of user (1 for Student, 2 for Admin).
        // @param name: The full name of the user.
        // @param username: The login username of the user.
        // @param password: The password for authentication.
        // @throws runtime_error: If called before the system has started.
        User ( int type , string name , string username, string password )
            : id ( ++ ID_START ) , type ( type ) , name ( name ) , username ( username ) , password ( password ) 
        {
            if ( !System::systemStarted() )
                throw runtime_error( "You cant Create a User before system runs" ) ;

            UserTable.insert( this ) ;
        }

        // Retrieves the unique identifier of this user.
        // @return: The ID of the user.
        int getId () const { return id ; }

        // Retrieves the full name of this user.
        // @return: The name as a string.
        string getName () const { return name ; }
        
        // Sets the name of this user.
        // @param value: The new name for the user.
        void setName ( string value ) { name = value ; }

        // Retrieves the login username of this user.
        // @return: The username as a string.
        string getUsername () const { return username ; }

        // Retrieves the type of this user.
        // @return: The user type (1 for Student, 2 for Admin).
        int getType () const { return type ; }
        
        // Sets the type of this user.
        // @param value: The new user type (1 for Student, 2 for Admin).
        void setType ( int value ) { type = value ; }

        // Displays the main menu for the user.
        // This is a virtual method to be overridden by subclasses (Student, Admin).
        virtual void mainMenu () ;

        // Displays the user account management menu.
        // Provides options for viewing profile, changing password, and logging out.
        void userMenu ()
        {
            string menuName = "User Account Menu" ;
            vector <string> menu = 
            {
                "View Profile",
                "Change Password",
                "Change Name",
                "Logout"
            } ;

            int chose = Utilities::prinitMenu( menuName , menu ) ;

            // some condations
        }

};

#endif