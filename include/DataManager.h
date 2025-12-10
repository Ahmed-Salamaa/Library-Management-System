#ifndef FILE_DATAMANAGER
#define FILE_DATAMANAGER

#include <bits/stdc++.h>
using namespace std;

const char DELIM = '\x1F';

class DataManager 
{
    private:

        // "data/"
        static const string DATA_PATH ;

        // Save functions
        template < typename t >
        static void saveToFile( const string & fileName , LinkedList <t*> & Table );

        // Load functions
        template < typename t >
        static void LoadFromFile( const string & fileName ) ;
        

    public:

        static void saveData();
        static void loadData();
        static void loadInitialData() ;
        
    private:

};


#endif