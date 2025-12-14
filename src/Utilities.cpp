#include <bits/stdc++.h>
using namespace std;

#include "../include/Utilities.h"

bool Utilities::validatePassword(const string &password)
{
    const int passwordmaxSize = 15;
    const int passwordMinSize = 8;

    const regex upper_case_expression{"[A-Z]+"};
    const regex lower_case_expression{"[a-z]+"};
    const regex number_expression{"[0-9]+"};
    const regex special_char_expression{"[@!?]+"};

    if (password.size() < passwordMinSize)
        throw runtime_error("Password must be at least " + to_string(passwordMinSize) + " characters long");

    if (password.size() > passwordmaxSize)
        throw runtime_error("Password must be at most " + to_string(passwordmaxSize) + " characters long");

    if (!regex_search(password, upper_case_expression))
        throw runtime_error("Password must contain at least one uppercase letter");

    if (!regex_search(password, lower_case_expression))
        throw runtime_error("Password must contain at least one lowercase letter");

    if (!regex_search(password, number_expression))
        throw runtime_error("Password must contain at least one digit");

    if (!regex_search(password, special_char_expression))
        throw runtime_error("Password must contain at least one special character");

    return true;
}

string Utilities::readPassword(istream &in, ostream &out)
{
    while (true)
    {
        try
        {
            string password = readString(in, out);
            validatePassword(password);
            return password;
        }
        catch (const runtime_error &e)
        {
            if (string(e.what()) == "User requested exit")
            {
                throw;
            }

            out << e.what() << '\n';
        }
    }
}

bool Utilities::validateUsername(const string &username)
{
    const int usernameMinSize = 3;
    const int usernameMaxSize = 20;
    const regex usernamePattern{"^[A-Za-z][A-Za-z0-9_]*$"};

    if (username.size() < usernameMinSize)
        throw runtime_error("Username must be at least " + to_string(usernameMinSize) + " characters long");

    if (username.size() > usernameMaxSize)
        throw runtime_error("Username must be at most " + to_string(usernameMaxSize) + " characters long");

    if (!regex_match(username, usernamePattern))
        throw runtime_error("Username must start with a letter and contain only letters, digits, or underscores");

    return true;
}

string Utilities::readUsername(istream &in, ostream &out)
{
    while (true)
    {
        try
        {
            string username = readString(in, out);
            validateUsername(username);
            return username;
        }
        catch (const runtime_error &e)
        {
            if (string(e.what()) == "User requested exit")
            {
                throw;
            }

            out << e.what() << '\n';
        }
    }
}

string Utilities::readString(istream &in, ostream &out)
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

int Utilities::readInt(istream &in, ostream &out)
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

int Utilities::readInt(int min, int max, istream &in, ostream &out)
{
    int value;
    while (true)
    {
        value = readInt(in, out);

        if (value >= min && value <= max)
            return value;
        else
        {
            out << "Number out of range! Please enter a number between "
                << min << " and " << max << " (or 'exit' to quit): ";
        }
    }
}

int Utilities::printMenu(const string &menuName, const vector<string> &menu, ostream &out)
{
    int maxWidth = menuName.size();
    for (const auto &item : menu)
    {
        int itemWidth = item.size() + 6;
        if (itemWidth > maxWidth)
            maxWidth = itemWidth;
    }

    maxWidth += 4;
    string horizontalLine(maxWidth, '=');

    out << "\n " << horizontalLine << " \n";

    int leftPad = (maxWidth - menuName.size()) / 2;
    int rightPad = maxWidth - menuName.size() - leftPad;
    out << "|" << string(leftPad, ' ') << menuName << string(rightPad, ' ') << "|\n";

    out << " " << horizontalLine << " \n";

    for (int i = 0; i < (int)(menu.size()); i++)
    {
        string item = "  " + to_string(i + 1) + ". " + menu[i];
        int padding = maxWidth - item.size();
        padding = max(0, padding);
        out << "|" << item << string(padding, ' ') << "|\n";
    }

    out << " " << horizontalLine << " \n";

    out << "Enter your choice (or 'exit' to quit) : ";
    return readInt(1, menu.size());
}

void Utilities::printData(const string &menuName, const vector<pair<string, string>> &menu, ostream &out)
{
    int maxWidth = menuName.size();
    for (const auto &[item1, item2] : menu)
    {
        int itemWidth = max(item1.size(), item2.size()) + 6;
        if (itemWidth > maxWidth)
            maxWidth = itemWidth;
    }

    maxWidth += 6;
    string horizontalLine(maxWidth, '=');

    out << "\n " << horizontalLine << " \n";

    int leftPad = (maxWidth - menuName.size()) / 2;
    int rightPad = maxWidth - menuName.size() - leftPad;
    out << "|" << string(leftPad, ' ') << menuName << string(rightPad, ' ') << "|\n";

    out << " " << horizontalLine << " \n";

    for (int i = 0; i < (int)(menu.size()); i++)
    {
        string item = "  " + menu[i].first + ": " + menu[i].second;
        int padding = maxWidth - menu[i].first.size() - menu[i].second.size() - 4;
        padding = max(0, padding);
        out << "|" << item << string(padding, ' ') << "|\n";
    }

    out << " " << horizontalLine << " \n";
}

void Utilities::printData(const vector<string> &menu, ostream &out)
{
    int maxWidth = 0;
    for (const auto &item : menu)
    {
        int itemWidth = item.size() + 6;
        if (itemWidth > maxWidth)
            maxWidth = itemWidth;
    }

    maxWidth += 6;
    string horizontalLine(maxWidth, '=');

    out << "\n " << horizontalLine << " \n";

    for (int i = 0; i < (int)(menu.size()); i++)
    {
        string item = "  " + menu[i];
        int padding = maxWidth - menu[i].size() - 2;
        padding = max(0, padding);
        out << "|" << item << string(padding, ' ') << "|\n";
    }

    out << " " << horizontalLine << " \n";
}

void Utilities::printData(const string &menuName, ostream &out)
{
    int maxWidth = menuName.size();

    maxWidth += 6;
    string horizontalLine(maxWidth, '=');

    out << "\n " << horizontalLine << " \n";

    int leftPad = (maxWidth - menuName.size()) / 2;
    int rightPad = maxWidth - menuName.size() - leftPad;
    out << "|" << string(leftPad, ' ') << menuName << string(rightPad, ' ') << "|\n";

    out << " " << horizontalLine << " \n";
}

void Utilities::setPassword(string &password, istream &in, ostream &out)
{
    while (true)
    {
        try
        {
            out << "Enter your old password: ";
            string oldPassword = Utilities::readPassword(in, out);
            if (oldPassword != password)
            {
                out << "Incorrect old password.Try again.\n";
                continue;
            }
            out << "Enter your new password: ";
            string newPassword = Utilities::readPassword(in, out);
            Utilities::validatePassword(newPassword);
            password = newPassword;
            out << "Password updated successfully!\n";
            return;
        }
        catch (const runtime_error &e)
        {
            if (string(e.what()) == "User requested exit")
            {
                throw;
            }
            out << e.what() << '\n';
        }
    }
}