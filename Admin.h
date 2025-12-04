#ifndef FILE_ADMIN
#define FILE_ADMIN

#include "User.h"

class Admin : public User
{
    public :

        Admin ( int id , string name , string password )
            : User( id , 2 , name , password ) {}

        Admin ( string name , string password )
            : User( 2 , name , password ) {}

        void mainMenu () override ;
} ;

#endif