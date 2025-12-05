#ifndef FILE_DATE
#define FILE_DATE

#include <bits/stdc++.h>
using namespace std;

class Date
{
    private :

    const static int lastDay[] ;

    int day;
    int month;
    int year;

    public :

    // Initializes a Date object with default values (01/01/2000).
    // @return: A new Date instance with day=1, month=1, year=2000.
    Date() : day(1), month(1), year(2000) {} ;

    // Checks if a given Date object represents a valid date.
    // @param other: The Date object to validate.
    // @return: True if the date is valid, false otherwise.
    bool validDate(Date &other)
    {
        int m = other.month, d = other.day, y = other.year;
        if (y < 0 || m < 1 || m > 12 || d < 1)
            return false;

        return d <= lastDay[m];
    }

    // Checks if the given day, month, and year represent a valid date.
    // @param d: The day value (1-31 depending on the month).
    // @param m: The month value (1-12).
    // @param y: The year value (must be non-negative).
    // @return: True if the date is valid, false otherwise.
    bool validDate(int d, int m, int y)
    {
        if (y < 0 || m < 1 || m > 12 || d < 1)
            return false;

        return d <= lastDay[m];
    }

    // Sets the date from another Date object.
    // @param other: The Date object to copy from.
    void setDate(const Date &other)
    {
        setDate(other.day, other.month, other.year);
    }

    // Sets the date from individual day, month, and year values.
    // Prompts the user to re-enter values if the date is invalid.
    // @param d: The day value.
    // @param m: The month value.
    // @param y: The year value.
    void setDate(int d, int m, int y)
    {
        while (!validDate(d, m, y))
        {
            cout << "Please enter a valid date: ";
            cin >> d >> m >> y;
        }

        this->day = d;
        this->month = m;
        this->year = y;
    }

    // Compares two dates to determine if this date is earlier than another.
    // @param T: The Date object to compare with.
    // @return: True if this date is earlier than T, false otherwise.
    bool operator<(const Date &T) const
    {
        if (year != T.year)
            return year < T.year;
        if (month != T.month)
            return month < T.month;
        return day < T.day;
    }

    // Assigns the value of another Date object to this Date object.
    // @param other: The Date object to copy from.
    // @return: A reference to this Date object.
    Date &operator=(const Date &other)
    {
        if (this == &other)
            return *this;

        day = other.day;
        month = other.month;
        year = other.year;

        return *this;
    }

    // Adds a specified number of days to this date.
    // @param days: The number of days to add.
    // @return: A new Date object representing the result date.
    Date operator + ( int days ) const
    {
        Date result = *this ;

        result.day += days ;

        while (true)
        {
            int ld = lastDay[result.month] ;

            if ( result.day <= ld ) break ;

            result.day -= ld ;
            result.month ++ ;

            if ( result.month > 12 )
            {
                result.month = 1 ;
                result.year ++ ;
            }
        }

        return result;
    }

    // Displays the date in DD/MM/YYYY format to the console.
    void display() const
    {
        cout << setw(2) << setfill('0') << day << "/"
             << setw(2) << setfill('0') << month << "/"
             << year << endl;
    }

    // Outputs a Date object to an output stream in string format.
    // @param out: The output stream to write to.
    // @param obj: The Date object to output.
    // @return: The output stream reference.
    friend ostream& operator<< ( ostream& out , Date obj )
    {
        out << obj.toString() ;
        return out ;
    }

    // Converts the date to a string representation in DD/MM/YYYY format.
    // @return: A string containing the formatted date.
    string toString() const
    {
        char buf[11];
        sprintf(buf, "%02d/%02d/%04d", day, month, year);
        return string(buf);
    }
};


#endif