#ifndef FILE_DATE
#define FILE_DATE

#include "System.h"

class Date
{
    private :

    const static int lastDay[] ;

    int day;
    int month;
    int year;

    public :

    Date() : day(1), month(1), year(2000) {} ;

    bool validDate(Date &other) // to check if date is valid date or not  (with date)
    {
        int m = other.month, d = other.day, y = other.year;
        if (y < 0 || m < 1 || m > 12 || d < 1)
            return false;

        return d <= lastDay[m];
    }

    bool validDate(int d, int m, int y) // to check if date is valid date or not
    {
        if (y < 0 || m < 1 || m > 12 || d < 1)
            return false;

        return d <= lastDay[m];
    }

    void setDate(const Date &other)
    {
        setDate(other.day, other.month, other.year);
    }

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

    bool operator<(const Date &T) const
    {
        if (year != T.year)
            return year < T.year;
        if (month != T.month)
            return month < T.month;
        return day < T.day;
    }

    Date &operator=(const Date &other)
    {
        if (this == &other)
            return *this;

        day = other.day;
        month = other.month;
        year = other.year;

        return *this;
    }

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

    Date operator+(int days) const
    {
        Date result = *this ;

        result.day += days ;

        while ( true )
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

        return result ;
    }

    void display() const
    {
        cout << setw(2) << setfill('0') << day << "/"
             << setw(2) << setfill('0') << month << "/"
             << year << endl;
    }

    friend ostream& operator<< ( ostream& out , Date obj )
    {
        out << obj.toString() ;
        return out ;
    }

    string toString() const
    {
        char buf[11];
        sprintf(buf, "%02d/%02d/%04d", day, month, year);
        return string(buf);
    }
};


#endif