#ifndef FILE_BOOK
#define FILE_BOOK

#include <iostream>
#include <string>
using namespace std;

#include "System.h"

class Book 
{
    private:

        static int ID_START ;

        const int id ;
        int quantity ;
        string title ;
        string author ;

    public:

        Book ( int id , const string & title , const string & author )
            : id ( id ) , quantity ( quantity ) , title ( title ) , author ( author )  
        {
            if ( !System::system_started() )
                throw runtime_error( "You cant Create a User with an setted id after system runs" ) ;
        }

        Book ( int id , const string & title , const string & author )
            : id ( ++ ID_START ) , quantity ( quantity ) , title ( title ) , author ( author )  
        {
            if ( !System::system_started() )
                throw runtime_error( "You cant Create a User before system runs" ) ;
        }


        int getId() const { return id ; }
        
        string getTitle() const { return title ; }
        void setTitle ( const string & title ) { this->title = title ; }

        string getAuthor() const { return author ; }
        void setAuthor ( const string & author ) { this->author = author ; }

};

int Book::ID_START = 1'000'000 ;


#endif

