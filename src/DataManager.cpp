#include "../include/LinkedList.h"
#include "../include/Utilities.h"
#include "../include/System.h"
#include "../include/Book.h"
#include "../include/User.h"
#include "../include/Admin.h"
#include "../include/Student.h"
#include "../include/Borrow.h"
#include "../include/DataManager.h"

// Define the static member
const string DataManager::DATA_PATH = string("data") + filesystem::path::preferred_separator;

// Save functions
template < typename t >
void DataManager::saveToFile( const string & fileName , LinkedList <t*> & Table )
{
    vector <t*> entity = Table.searchAllByPredicate ( []( t* const & obj ) { return true ; } ) ;
    
    string filePath = DATA_PATH + fileName ;

    ofstream file ( filePath ) ;

    if ( !file.is_open() ) return ;

    file << t::ID_START << " " << entity.size() << "\n" ;

    for ( auto obj : entity )
    {
        if ( obj ) 
            file << obj->toCSV() << "\n" ;
    }

    file.close() ;
}


void DataManager::saveData()
{
    filesystem::create_directories( DATA_PATH ) ;

    saveToFile<Book>( "book.dat" , Book::BookTable ) ;
    saveToFile<User>( "user.dat" , User::UserTable ) ;
    saveToFile<Borrow>( "Borrow.dat" , Borrow::BorrowTable ) ;
}


// Load functions
template < typename t >
void DataManager::LoadFromFile( const string & fileName )
{
    string filePath = DATA_PATH + fileName ;

    ifstream file ( filePath ) ;

    if ( !file.is_open() ) throw runtime_error( "Fail to load" ) ; 
    
    int cnt ;
    file >> t::ID_START >> cnt ;
    file.ignore() ;

    while ( cnt -- )
    {
        string entity ;
        getline( file , entity ) ;
        
        if ( !entity.empty() )
            t::fromCSV( entity ) ;
    }

    file.close() ;
}

void DataManager::loadInitialData()
{
    // Create initial books (BEFORE system starts)
    new Book( 5, "C++ Programming", "Bjarne Stroustrup");
    new Book( 3, "Clean Code", "Robert Martin");
    new Book( 7, "Design Patterns", "Gang of Four");
    new Book( 2, "The Pragmatic Programmer", "Hunt & Thomas");
    new Book( 4, "Introduction to Algorithms", "Cormen");

    // Create initial admin (BEFORE system starts)
    new Admin( "Admin User", "admin", "Admin@123");

    // Create initial students (BEFORE system starts)
    new Student( "Rasha Jouda", "rasha", "Rasha@123");
    new Student( "Sara Ali", "sara", "Sara@123");
}

void DataManager::loadData()
{
    filesystem::create_directories( DATA_PATH ) ;

    LoadFromFile < Book > ( "book.dat" ) ;
    LoadFromFile < User > ( "user.dat" ) ;
    LoadFromFile < Borrow > ( "Borrow.dat" ) ;

}
