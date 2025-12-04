#ifndef FILE_USER
#define FILE_USER

#include "System.h"

class User
{
    private:

        static LinkedList < User * > UserTable ;
        static int ID_START ;

    protected:

        const int id;
        string name , username , password ;

        // type = 1 for Student
        // type = 2 for Admin
        int type;

    public:

        static User * getPointer ( int id ) { return UserTable.search( id ) ; }
        static User * getPointer ( string username ) { return UserTable.search( username ) ; }

        static void deleteUser ( User * ptr )
        {
            if ( !ptr ) throw runtime_error( "Cannot delete user: Invalid reference") ;

            UserTable.erase( ptr ) ;
        }

        static void deleteUser ( int id )
        {
            User * ptr ;

            if ( ptr ) deleteUser( ptr ) ;
            else throw runtime_error( "Cannot delete user: No user found with ID " + to_string(id) ) ;
        }

        User ( int id , int type , string name , string username , string password )
            : id ( id ) , type ( type ) , name ( name ) , username ( username ) , password ( password ) 
        {
            if ( System::systemStarted() )
                throw runtime_error( "You cant Create a User with an setted id after system runs" ) ;

            UserTable.insert( this ) ;
        }

        User ( int type , string name , string username, string password )
            : id ( ++ ID_START ) , type ( type ) , name ( name ) , username ( username ) , password ( password ) 
        {
            if ( !System::systemStarted() )
                throw runtime_error( "You cant Create a User before system runs" ) ;

            UserTable.insert( this ) ;
        }

        bool operator == ( const User & rhs ) { return id == rhs.id ; }
        bool operator != ( const User & rhs ) { return id != rhs.id ; }

        bool operator == ( const int & rhs ) { return id == rhs ; }
        bool operator != ( const int & rhs ) { return id != rhs ; }

        bool operator == ( const string & rhs ) { return username == rhs ; }
        bool operator != ( const string & rhs ) { return username != rhs ; }

        int getId () const { return id ; }

        string getName () const { return name ; }
        void setName ( string value ) { name = value ; }

        string getUsername () const { return username ; }
        void setUsername ( string value ) { username = value ; }

        int getType () const { return type ; }
        void setType ( int value ) { type = value ; }

        
        virtual void mainMenu () ;
        
};





#endif