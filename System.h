#ifndef FILE_SYSTEM
#define FILE_SYSTEM


#include "LinkedList.h"
#include "User.h"
#include "Book.h"


class System
{
    private :

        static LinkedList < User * > UsersTable ;
        static LinkedList < Book * > UsersTable ;


    public :

        static bool system_started () ;

};



#endif