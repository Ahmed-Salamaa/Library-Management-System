#ifndef FILE_STUDENT
#define FILE_STUDENT

#include "User.h"

class Student : public User
{
    public :

        Student ( int id , string name , string password )
            : User( id , 1 , name , password ) {}

        Student ( string name , string password )
            : User( 1 , name , password ) {}

        void mainMenu () override ;
} ;

#endif