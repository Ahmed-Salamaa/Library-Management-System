#ifndef FILE_LINKED_LIST
#define FILE_LINKED_LIST

template < typename t >
class LinkedList
{
    public :

        void insert ( t obj ) ;
        t search ( int id ) ;
        t search ( string name ) ;

        void erase ( t obj ) ;
        void erase ( int id ) ;
} ;

#endif