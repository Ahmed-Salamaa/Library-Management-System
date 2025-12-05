#ifndef FILE_SYSTEM
#define FILE_SYSTEM

#include <bits/stdc++.h>
using namespace std;

#include "LinkedList.h"
#include "User.h"
#include "Book.h"
#include "Borrow.h"

class System
{
    private :

        static bool systemState ;

    public :

        static User * currPtr ;
        
        // Checks whether the system has been started.
        // @return: True if the system has been initialized, false otherwise.
        static bool systemStarted () { return systemState ; }

};

int Borrow::ID_START = 1'000'000 ;
int   User::ID_START = 1'000'000 ;
int   Book::ID_START = 1'000'000 ;


User * System::currPtr = nullptr ;
bool System::systemState = false ;



#endif