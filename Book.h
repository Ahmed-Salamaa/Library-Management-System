#ifndef FILE_BOOK
#define FILE_BOOK

#include "System.h"

class Book 
{
    private:

        static LinkedList < Book * > BookTable ;
        static int ID_START ;

        const int id ;
        int quantity ;
        string title ;
        string author ;

    public:

        static Book * getPointer ( int id ) { return BookTable.search( id ) ; }
        static Book * getPointer ( string title ) { return BookTable.search( title ) ; }

        static void deleteBook ( Book * ptr )
        {
            if ( !ptr ) throw runtime_error( "Cannot delete Book: Invalid reference") ;

            BookTable.erase( ptr ) ;
        }

        static void deleteBook ( int id )
        {
            Book * ptr ;

            if ( ptr ) deleteBook( ptr ) ;
            else throw runtime_error( "Cannot delete Book: No Book found with ID " + to_string(id) ) ;
        }

        Book ( int id , int quantity , const string & title , const string & author )
            : id ( id ) , quantity ( quantity ) , title ( title ) , author ( author )  
        {
            if ( System::systemStarted() )
                throw runtime_error( "You cant Create a User with an setted id after system runs" ) ;

            BookTable.insert( this ) ;
        }

        Book ( int id , int quantity , const string & title , const string & author )
            : id ( ++ ID_START ) , quantity ( quantity ) , title ( title ) , author ( author )  
        {
            if ( !System::systemStarted() )
                throw runtime_error( "You cant Create a User before system runs" ) ;
        
            BookTable.insert( this ) ;
        }

        bool operator == ( const Book & rhs ) { return id == rhs.id ; }
        bool operator != ( const Book & rhs ) { return id != rhs.id ; }

        bool operator == ( const int & rhs ) { return id == rhs ; }
        bool operator != ( const int & rhs ) { return id != rhs ; }

        bool operator == ( const string & rhs ) { return title == rhs ; }
        bool operator != ( const string & rhs ) { return title != rhs ; }

        int getId() const { return id ; }
        
        string getTitle() const { return title ; }
        void setTitle ( const string & title ) { this->title = title ; }

        string getAuthor() const { return author ; }
        void setAuthor ( const string & author ) { this->author = author ; }

};




#endif

