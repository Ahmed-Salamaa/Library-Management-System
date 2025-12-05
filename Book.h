#ifndef FILE_BOOK
#define FILE_BOOK

#include <bits/stdc++.h>
using namespace std;

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

        // Retrieves a pointer to a Book object by its ID.
        // @param id: The ID of the book to search for.
        // @return: A pointer to the Book object if found, or nullptr otherwise.
        // @throws runtime_error: If no book with the given ID exists.
        static Book *getPointer(int id)
        {
            function < bool( Book * ) > condition = [&] ( Book * obj )
            {
                return obj->getId() == id ;
            };
            
            return BookTable.search( condition );
        }

        // Retrieves a pointer to a Book object by its title.
        // @param title: The title of the book to search for.
        // @return: A pointer to the Book object if found, or nullptr otherwise.
        // @throws runtime_error: If no book with the given title exists.
        static Book *getPointer( string title )
        {
            function < bool( Book * ) > condition = [&] ( Book * obj )
            {
                return obj->getTitle() == title ;
            };
            
            return BookTable.search( condition );
        }

        // Deletes a Book object from the book table using a pointer reference.
        // @param ptr: A pointer to the Book object to delete.
        // @throws runtime_error: If the pointer is invalid (nullptr).
        static void deleteBook ( Book * ptr )
        {
            if ( !ptr ) throw runtime_error( "Cannot delete Book: Invalid reference") ;

            function < bool( Book * ) > condition = [&] ( Book * obj )
            {
                return obj == ptr ;
            };

            BookTable.erase( condition ) ;
        }

        // Deletes a Book object from the book table using its ID.
        // @param id: The ID of the book to delete.
        // @throws runtime_error: If no book with the given ID exists.
        static void deleteBook ( int id )
        {
            Book * ptr  = getPointer(id);

            if ( ptr ) deleteBook( ptr ) ;
            else throw runtime_error( "Cannot delete Book: No Book found with ID " + to_string(id) ) ;
        }

        // Initializes a Book object with a predefined ID (used during system initialization).
        // @param id: The unique identifier for the book (must be set before system starts).
        // @param quantity: The number of copies available.
        // @param title: The title of the book.
        // @param author: The author of the book.
        // @throws runtime_error: If called after the system has started.
        Book ( int id , int quantity , const string & title , const string & author )
            : id ( id ) , quantity ( quantity ) , title ( title ) , author ( author )  
        {
            if ( System::systemStarted() )
                throw runtime_error( "You cant Create a User with an setted id after system runs" ) ;

            BookTable.insert( this ) ;
        }

        // Initializes a Book object with an auto-generated ID (used during runtime).
        // @param quantity: The number of copies available.
        // @param title: The title of the book.
        // @param author: The author of the book.
        // @throws runtime_error: If called before the system has started.
        Book ( int quantity , const string & title , const string & author )
            : id ( ++ ID_START ) , quantity ( quantity ) , title ( title ) , author ( author )  
        {
            if ( !System::systemStarted() )
                throw runtime_error( "You cant Create a User before system runs" ) ;
        
            BookTable.insert( this ) ;
        }

        // Retrieves the unique identifier of this book.
        // @return: The ID of the book.
        int getId() const { return id ; }
        
        // Retrieves the title of this book.
        // @return: The title as a string.
        string getTitle() const { return title ; }
        
        // Sets the title of this book.
        // @param title: The new title for the book.
        void setTitle ( const string & title ) { this->title = title ; }

        // Retrieves the author of this book.
        // @return: The author as a string.
        string getAuthor() const { return author ; }
        
        // Sets the author of this book.
        // @param author: The new author for the book.
        void setAuthor ( const string & author ) { this->author = author ; }

        // Checks if a book is available for borrowing.
        // @param BookId: The ID of the book to check.
        // @return: True if the book exists and has quantity greater than 0, false otherwise.
        static bool isAvailable(int BookId)
        {
            try
            {
                Book *book = getPointer(BookId);
                return getPointer(BookId)->quantity > 0;
            }
            catch (runtime_error &e)
            {
                return false;
            }
        }

};




#endif

