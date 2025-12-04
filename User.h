#ifndef FILE_USER
#define FILE_USER

#include <iostream>
#include <string>
using namespace std;

#include "System.h"

class User
{
    private:

        static int ID_START ;

    protected:

        const int id;
        string name, password;

        // type = 1 for Student
        // type = 2 for Admin
        int type;

    public:

        User ( int id , int type , string name , string password )
            : id ( id ) , type ( type ) , name ( name ) , password ( password ) 
        {
            if ( !System::system_started() )
                throw runtime_error( "You cant Create a User with an setted id after system runs" ) ;
        }

        User ( int type , string name , string password )
            : id ( ++ ID_START ) , type ( type ) , name ( name ) , password ( password ) 
        {
            if ( !System::system_started() )
                throw runtime_error( "You cant Create a User before system runs" ) ;
        }


        int getId () const { return id ; }

        string getName () const { return name ; }
        void setName ( string value ) { name = value ; }

        int getType () const { return type ; }
        void setType ( int value ) { type = value ; }
        
                
        virtual void mainMenu () ;
        
};

int User::ID_START = 1'000'000 ;




#endif