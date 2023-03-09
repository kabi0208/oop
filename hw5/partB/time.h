#include <iostream>
using namespace std;

class Time{
    friend ostream & operator<<(ostream &, const Time&); // output
    friend istream & operator>>(istream &, Time&); // input
    friend Time operator+(const Time&, const Time&); // addition 
    friend Time operator-(const Time&, const Time&); // substraction
    private:
        int day, hour, minute, second;
    public:
        Time(); // constructer without parameter
        Time(int); // constructer with one parameter (second)
        Time(int, int, int, int); // constructer with four parameter (all)

        int get_day() const; // get the value of day
        int get_hour() const; // get the value of hour
        int get_minute() const; // get the value of minute
        int get_second() const; // get the value of second
        
        bool operator<=(const Time&) const; // check if the time is equal to or less than another
        bool operator>=(const Time&) const; // check if the time is equal to or more than another
        bool operator==(const Time&) const; // check if the time is equal to another
        bool operator!=(const Time&) const; // check if the time is not equal to another
        bool operator<(const Time&) const; // check if the time is less than another
        bool operator>(const Time&) const; // check if the time is more than another
        
        Time& operator++(); // the second of time = time + 1;
        Time operator++(int); // the second of time = time + 1;
        Time& operator--(); // the second of time = time - 1;
        Time operator--(int); // the second of time = time - 1;
};

ostream & operator<<(ostream &,const Time&); // output
istream & operator>>(istream &, Time&); // input

Time operator+(const Time&, const Time&); // addition 
Time operator-(const Time&, const Time&); // substraction


