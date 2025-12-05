#ifndef FILE_UTILITIES
#define FILE_UTILITIES

#include <bits/stdc++.h>
using namespace std;

class Utilities
{
    public :

        // Validates password complexity and throws descriptive errors when invalid.
        // Requirements enforced: length bounds, at least one uppercase, lowercase, digit, and special character.
        // @param password: The password string to validate.
        // @throws runtime_error: With a message describing the first failing rule.
        // @return true when the password satisfies all rules.
        static bool validatePassword ( const string & password )
        {
            // password constains

            const int passwordmaxSize = 15 ;
            const int passwordMinSize = 8 ;

            const regex upper_case_expression { "[A-Z]+" }; //here is the very simple expression for upper_case search
            const regex lower_case_expression { "[a-z]+" }; //for lower-case
            const regex number_expression { "[0-9]+" }; //...
            const regex special_char_expression { "[@!?]+"};

            if ( password.size() < passwordMinSize )
                throw runtime_error( "Password must be at least " + to_string(passwordMinSize) + " characters long" );

            if ( password.size() > passwordmaxSize )
                throw runtime_error( "Password must be at most " + to_string(passwordmaxSize) + " characters long" );

            if ( !regex_search( password , upper_case_expression ) )
                throw runtime_error( "Password must contain at least one uppercase letter" );

            if ( !regex_search( password , lower_case_expression ) )
                throw runtime_error( "Password must contain at least one lowercase letter" );

            if ( !regex_search( password , number_expression ) )
                throw runtime_error( "Password must contain at least one digit" );

            if ( !regex_search( password , special_char_expression ) )
                throw runtime_error( "Password must contain at least one special character" );

            return true ;
        }

        // Reads a password from input, validates it, and prints validation errors.
        // @param in: Input stream to read from.
        // @param out: Output stream to print prompts and errors.
        // @return A password that satisfies all validation rules.
        // @throws runtime_error: Propagates if the user requests exit from readString.
        static string readPassword( istream& in = cin , ostream& out = cout )
        {
            while (true)
            {
                try
                {
                    string password = readString( in , out ) ;
                    validatePassword( password ) ;
                    return password ;
                }
                catch ( const runtime_error & e )
                {
                    if ( string( e.what() ) == "User requested exit" )
                    {
                        throw ;
                    }
                        
                    out << e.what() << '\n' ;
                }
            }
        }

        // Validates username format and throws descriptive errors when invalid.
        // Requirements enforced: length bounds, starts with a letter, and contains only letters, digits, or underscores.
        // @param username: The username string to validate.
        // @throws runtime_error: With a message describing the first failing rule.
        // @return true when the username satisfies all rules.
        static bool validateUsername ( const string & username )
        {
            const int usernameMinSize = 3 ;
            const int usernameMaxSize = 20 ;
            const regex usernamePattern { "^[A-Za-z][A-Za-z0-9_]*$" } ;

            if ( username.size() < usernameMinSize )
                throw runtime_error( "Username must be at least " + to_string(usernameMinSize) + " characters long" );

            if ( username.size() > usernameMaxSize )
                throw runtime_error( "Username must be at most " + to_string(usernameMaxSize) + " characters long" );

            if ( !regex_match( username , usernamePattern ) )
                throw runtime_error( "Username must start with a letter and contain only letters, digits, or underscores" );

            return true ;
        }

        // Reads a username from input, validates it, and prints validation errors.
        // @param in: Input stream to read from.
        // @param out: Output stream to print prompts and errors.
        // @return A username that satisfies all validation rules.
        // @throws runtime_error: Propagates if the user requests exit from readString.
        static string readUsername( istream& in = cin , ostream& out = cout )
        {
            while (true)
            {
                try
                {
                    string username = readString( in , out ) ;
                    validateUsername( username ) ;
                    return username ;
                }
                catch ( const runtime_error & e )
                {
                    if ( string( e.what() ) == "User requested exit" )
                    {
                        throw ;
                    }

                    out << e.what() << '\n' ;
                }
            }
        }

        // Reads a string input from the user with validation.
        // @return The validated string input from the user (strips leading/trailing whitespace).
        // @throws runtime_error: If the user enters "exit" to quit or provides an empty string.
        static string readString( istream& in , ostream& out )
        {
            string input;
            
            while (true)
            {
                getline(in, input);
                
                // Trim leading and trailing whitespace
                size_t start = input.find_first_not_of(" \t\n\r");
                size_t end = input.find_last_not_of(" \t\n\r");
                
                if (start == string::npos)
                {
                    out << "Invalid input! Please enter a non-empty string (or 'exit' to quit): ";
                    continue;
                }
                
                input = input.substr(start, end - start + 1);
                
                if (input == "exit" || input == "EXIT")
                {
                    throw runtime_error("User requested exit");
                }
                
                if (!input.empty())
                {
                    return input;
                }
                
                out << "Invalid input! Please enter a non-empty string (or 'exit' to quit): ";
            }
        }

        // Reads an integer input from the user with validation.
        // @return The validated integer input from the user.
        // @throws runtime_error: If the user enters "exit" to quit.
        static int readInt( istream& in , ostream& out )
        {
            string input;
            int value;
            
            while (true)
            {
                in >> input;
                
                if (input == "exit" || input == "EXIT")
                {
                    throw runtime_error("User requested exit");
                }
                
                stringstream ss(input);
                if (ss >> value && ss.eof())
                {
                    in.ignore(numeric_limits<streamsize>::max(), '\n');
                    return value;
                }
                
                in.clear();
                in.ignore(numeric_limits<streamsize>::max(), '\n');
                out << "Invalid input! Please enter a valid number (or 'exit' to quit): ";
            }
        }

        // Reads an integer input from the user with range validation.
        // @param min: The minimum acceptable value (inclusive).
        // @param max: The maximum acceptable value (inclusive).
        // @return The validated integer input within the specified range.
        static int readInt(int min, int max , istream& in = cin , ostream& out = cout )
        {
            int value;
            while (true)
            {
                value = readInt( in , out ) ;
                
                if (value >= min && value <= max) return value;
                else
                {
                    out << "Number out of range! Please enter a number between " 
                         << min << " and " << max << ": ";
                }
            }
        }

        // Prints a formatted menu with a title and numbered options.
        // @param menuName: The title of the menu to display.
        // @param menu: A vector of strings representing the menu options.
        // @return The user's menu choice (1-based index).
        static int printMenu ( const string & menuName , const vector <string>& menu , ostream& out = cout )
        {
            int maxWidth = menuName.size();
            for (const auto& item : menu)
            {
                int itemWidth = item.size() + 6; // 6 for "  X. " prefix
                if (itemWidth > maxWidth) maxWidth = itemWidth;
            }
            
            maxWidth = max(maxWidth, (int)30) + 4;
            string horizontalLine ( maxWidth , '=' ) ;
            
            out << "\n╔" << horizontalLine << "╗\n";
            
            int leftPad = (maxWidth - menuName.size()) / 2;
            int rightPad = maxWidth - menuName.size() - leftPad;
            out << "║" << string(leftPad, ' ') << menuName << string(rightPad, ' ') << "║\n";
            
            out << "╠" << horizontalLine << "╣\n";
            
            for ( int i = 0 ; i < (int)(menu.size()) ; i ++ )
            {
                string item = "  " + to_string(i + 1) + ". " + menu[i];
                int padding = maxWidth - item.size();
                out << "║" << item << string(padding, ' ') << "║\n";
            }
            
            out << "╚" << horizontalLine << "╝\n";
            
            out << "Enter your choice: " ;
            return readInt(1, menu.size());
        }

        // Displays formatted key-value data in a box.
        // @param out: The output stream to write to.
        // @param menuName: The title of the data display.
        // @param menu: A vector of key-value pairs to display.
        static void printData ( const string & menuName , const vector < pair<string,string> > & menu , ostream& out )
        {
            int maxWidth = menuName.size();
            for (const auto& [ item1 , item2 ] : menu)
            {
                int itemWidth = max( item1.size() , item2.size() ) + 6; // 6 for "  X. " prefix
                if (itemWidth > maxWidth) maxWidth = itemWidth;
            }
            
            maxWidth = max(maxWidth, (int)30) + 4;
            string horizontalLine ( maxWidth , '=' ) ;
            
            out << "\n╔" << horizontalLine << "╗\n";
            
            int leftPad = (maxWidth - menuName.size()) / 2;
            int rightPad = maxWidth - menuName.size() - leftPad;
            out << "║" << string(leftPad, ' ') << menuName << string(rightPad, ' ') << "║\n";
            
            out << "╠" << horizontalLine << "╣\n";
            
            for ( int i = 0 ; i < (int)(menu.size()) ; i ++ )
            {
                string item = "  " + menu[i].first + ": " + menu[i].second;
                int padding = maxWidth - menu[i].first.size() + menu[i].second.size() ;
                out << "║" << item << string(padding, ' ') << "║\n";
            }
            
            out << "╚" << horizontalLine << "╝\n";
        }
};

#endif