#ifndef FILE_LINKED_LIST
#define FILE_LINKED_LIST

template < typename t >
class LinkedList
{
    private :

        struct node
        {
            t data ;
            node * next ;

            node () : data () , next ( nullptr ) {} ;
            node ( t val ) : data ( val ) , next ( nullptr ) {} ;

            bool operator == ( const node & rhs ) { return data == rhs.data ; }
            bool operator != ( const node & rhs ) { return data != rhs.data ; }
        };

        node * head ;
        int size ;

    public :

        LinkedList () : head ( nullptr ) , size ( 0 ) {} ;

        void insert ( t obj ) ;
        t search ( int id ) ;
        t search ( string name ) ;

        void erase ( t obj ) ;
        void erase ( int id ) ;


} ;

#endif