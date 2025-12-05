#ifndef FILE_UTILITIES
#define FILE_UTILITIES

#include <bits/stdc++.h>
using namespace std;

class Utilities
{
    public :

        // Reads an integer input from the user with validation.
        // @return: The validated integer input from the user.
        // @throws runtime_error: If the user enters "exit" to quit.
        static int readInt()
        {
            string input;
            int value;
            
            while (true)
            {
                cin >> input;
                
                if (input == "exit" || input == "EXIT")
                {
                    throw runtime_error("User requested exit");
                }
                
                stringstream ss(input);
                if (ss >> value && ss.eof())
                {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    return value;
                }
                
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a valid number (or 'exit' to quit): ";
            }
        }

        // Reads an integer input from the user with range validation.
        // @param min: The minimum acceptable value (inclusive).
        // @param max: The maximum acceptable value (inclusive).
        // @return: The validated integer input within the specified range.
        static int readInt(int min, int max)
        {
            int value;
            while (true)
            {
                value = readInt() ;
                
                if (value >= min && value <= max) return value;
                else
                {
                    cout << "Number out of range! Please enter a number between " 
                         << min << " and " << max << ": ";
                }
            }
        }

        // Prints a formatted menu with a title and numbered options.
        // @param menuName: The title of the menu to display.
        // @param menu: A vector of strings representing the menu options.
        // @return: The user's menu choice (1-based index).
        static int prinitMenu ( string menuName , vector <string> menu )
        {
            int maxWidth = menuName.size();
            for (const auto& item : menu)
            {
                int itemWidth = item.size() + 6; // 6 for "  X. " prefix
                if (itemWidth > maxWidth) maxWidth = itemWidth;
            }
            
            maxWidth = max(maxWidth, (int)30) + 4;
            string horizontalLine ( maxWidth , '=' ) ;
            
            cout << "\n╔" << horizontalLine << "╗\n";
            
            int leftPad = (maxWidth - menuName.size()) / 2;
            int rightPad = maxWidth - menuName.size() - leftPad;
            cout << "║" << string(leftPad, ' ') << menuName << string(rightPad, ' ') << "║\n";
            
            cout << "╠" << horizontalLine << "╣\n";
            
            for ( int i = 0 ; i < menu.size() ; i ++ )
            {
                string item = "  " + to_string(i + 1) + ". " + menu[i];
                int padding = maxWidth - item.size();
                cout << "║" << item << string(padding, ' ') << "║\n";
            }
            
            cout << "╚" << horizontalLine << "╝\n";
            
            cout << "Enter your choice: " ;
            return readInt(1, menu.size());
        }
};

#endif