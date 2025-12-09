#ifndef FILE_UTILITIES
#define FILE_UTILITIES

#include <bits/stdc++.h>
using namespace std;

class Utilities
{
public:
    // Validates password complexity and throws descriptive errors when invalid.
    // Requirements enforced: length bounds, at least one uppercase, lowercase, digit, and special character.
    // @param password: The password string to validate.
    // @throws runtime_error: With a message describing the first failing rule.
    // @return true when the password satisfies all rules.
    static bool validatePassword(const string &password) ;
   
    // Reads a password from input, validates it, and prints validation errors.
    // @param in: Input stream to read from.
    // @param out: Output stream to print prompts and errors.
    // @return A password that satisfies all validation rules.
    // @throws runtime_error: Propagates if the user requests exit from readString.
    static string readPassword(istream &in = cin, ostream &out = cout) ;

    // Validates username format and throws descriptive errors when invalid.
    // Requirements enforced: length bounds, starts with a letter, and contains only letters, digits, or underscores.
    // @param username: The username string to validate.
    // @throws runtime_error: With a message describing the first failing rule.
    // @return true when the username satisfies all rules.
    static bool validateUsername(const string &username) ;

    // Reads a username from input, validates it, and prints validation errors.
    // @param in: Input stream to read from.
    // @param out: Output stream to print prompts and errors.
    // @return A username that satisfies all validation rules.
    // @throws runtime_error: Propagates if the user requests exit from readString.
    static string readUsername(istream &in = cin, ostream &out = cout) ;

    // Reads a string input from the user with validation.
    // @return The validated string input from the user (strips leading/trailing whitespace).
    // @throws runtime_error: If the user enters "exit" to quit or provides an empty string.
    static string readString(istream &in = cin, ostream &out = cout) ;

    // Reads an integer input from the user with validation.
    // @return The validated integer input from the user.
    // @throws runtime_error: If the user enters "exit" to quit.
    static int readInt(istream &in, ostream &out) ;

    // Reads an integer input from the user with range validation.
    // @param min: The minimum acceptable value (inclusive).
    // @param max: The maximum acceptable value (inclusive).
    // @return The validated integer input within the specified range.
    static int readInt(int min, int max, istream &in = cin, ostream &out = cout) ;

    // Prints a formatted menu with a title and numbered options.
    // @param menuName: The title of the menu to display.
    // @param menu: A vector of strings representing the menu options.
    // @return The user's menu choice (1-based index).
    static int printMenu(const string &menuName, const vector<string> &menu, ostream &out = cout) ;

    // Displays formatted key-value data in a box.
    // @param menuName: The title of the data display.
    // @param menu: A vector of key-value pairs to display.
    // @param out: The output stream to write to.
    static void printData(const string &menuName, const vector<pair<string, string>> &menu, ostream &out) ;

    // Displays formatted key-value data in a box.
    // @param menu: A vector of key-value pairs to display.
    // @param out: The output stream to write to.
    static void printData( const vector<string> &menu, ostream &out) ;

    // Displays formatted data in a box.'
    // @param menuName: The title of the data display.
    // @param out: The output stream to write to.
    static void printData(const string &menuName, ostream &out) ;

    static void setPassword(string &password, istream &in = cin, ostream &out = cout) ;

};

#endif