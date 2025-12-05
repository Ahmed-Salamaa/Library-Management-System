#include <bits/stdc++.h>
using namespace std;

#include "Utilities.h"

int main() {



            string menuName = "User Account Menu" ;
            vector <string> menu = 
            {
                "View Profile",
                "Change Password",
                "Change Name",
                "Logout"
            } ;

            int chose = Utilities::printMenu( menuName , menu , cout ) ;


    return 0;
}