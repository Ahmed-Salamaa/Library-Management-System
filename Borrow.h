#ifndef FILE_BORROW
#define FILE_BORROW

#include "System.h"

class Borrow
{
    private :

        static LinkedList < Borrow * > BorrowTable ;
        static int ID_START ;

        const int id ;
        const int UserId ;
        const int BookId ;
        const Date borrowDate ;
        Date returnDate ;
        bool status ;

    public :

        static Borrow * getPointer ( int id ) { return BorrowTable.search( id ) ; }
        static Borrow * getPointer ( string title ) { return BorrowTable.search( title ) ; }

        Borrow ( int id , int UserId , int BookId , Date borrowDate , Date returnDate , bool status )
            : id ( id ) , UserId ( UserId ) , BookId ( BookId ) 
            , borrowDate ( borrowDate ) , returnDate ( returnDate ) , status ( status )
        {
            if ( System::systemStarted() )
                throw runtime_error( "You cant Create a Borrow object with an setted id after system runs" ) ;

            BorrowTable.insert( this ) ;
        }

        Borrow ( int UserId , int BookId , Date borrowDate , Date returnDate , bool status )
            : id ( ++ ID_START ) , UserId ( UserId ) , BookId ( BookId ) 
            , borrowDate ( borrowDate ) , returnDate ( returnDate ) , status ( status )
        {
            if ( !System::systemStarted() )
                throw runtime_error( "You cant Create a Borrow object before system runs" ) ;

            BorrowTable.insert( this ) ;
        }

        Borrow ( int UserId , int BookId , Date borrowDate , Date returnDate , bool status )
            : id ( ++ ID_START ) , UserId ( UserId ) , BookId ( BookId ) 
            , borrowDate ( borrowDate ) , returnDate ( borrowDate + 3 ) , status ( status )
        {
            if ( !System::systemStarted() )
                throw runtime_error( "You cant Create a Borrow object before system runs" ) ;

            BorrowTable.insert( this ) ;
        }

        int getId () const { return id ; }
        int getUserId () const { return UserId ; }
        int getBookId () const { return BookId ; }

        Date getBorrowDate () const { return borrowDate ; }

        Date getReturnDate () const { return returnDate ; }
        void setReturnDate ( Date value ) { returnDate = value ; }

        bool getStatus () const { return status ; }
        void setStatus ( bool value ) { status = value ; }
        
};


#endif