#include <bits/stdc++.h>
using namespace std;

#include "Utilities.h"
// #include "User.h"
// #include "Admin.h"
// #include "Book.h"
// #include "Borrow.h"
// #include "LinkedList.h"

int main() {

        string menuName = "Book Info";
        const vector<pair<string, string>> menu =
            {
                {"Quantity", to_string(150)},
                {"Title", "Introduction to Algorithms"},
                {"Author", "Cormen                              d"}};

        Utilities::printData(menuName, menu,cout);



            // string menuName = "User Account Menu" ;
            // vector <string> menu = 
            // {
            //     "View Profile",
            //     "Change Password",
            //     "Change Name",
            //     "Logout"
            // } ;

            // int chose = Utilities::printMenu( menuName , menu , cout ) ;


    return 0;
}