#include <iostream>
#include <cstring>
#include "time.h"
#include <iomanip>

using namespace std;

int Time::get_day() const{ return day; } // get the value of day
int Time::get_hour() const{ return hour; } // get the value of hour
int Time::get_minute() const{ return minute; } // get the value of minute
int Time::get_second() const{ return second; } // get the value of second

Time::Time(){ // constructer without parameter
     // initialize everything to 0
    day = 0;
    hour = 0;
    minute = 0;
    second = 0;
}

Time::Time(int s){  // constructer with one parameter (second)
    if(s < 0){ //  If the parameter is negative, default the Time object to represent 0.
        day = 0, hour = 0, minute = 0, second = 0;
        cout << "The parameter is less than 0, default the Time object to represent 0." << endl;
    }
    else{ // translated second(s) into the appropriate notation for a Time object.
        day = s / 60 / 60 / 24;
        hour = s / 60 / 60 - (day * 24);
        minute = s / 60 - (day * 24 * 60 + hour * 60);
        second = s - (day * 24 * 60 * 60 + hour * 60 * 60 + minute * 60);
    }
}

Time::Time(int d, int h, int m, int s){ // constructer with four parameter (all)
    // If any of the provided values are negative, default the Time object to represent 0.
    if(s < 0 || m < 0 || h < 0 || d < 0){ 
        second = 0, minute = 0, hour = 0, day = 0;
        cout << "At least one parameter is less than 0, default the Time object to represent 0." << endl;
    }
    else{
        second = s, minute = m, hour = h, day = d;
        // simplify the object to the appropriate representation.
        while(second >= 60){ 
            second -= 60;
            minute++;
        }
        while(minute >= 60){
            minute -= 60;
            hour++;
        }
        while(hour >= 24){
            hour -= 24;
            day++;
        }
    }
    
}

ostream & operator<<(ostream & cout,const Time& goal){ // output
    cout << goal.day << "~" ;
    cout << setfill('0') << setw(2) << goal.hour << ":" ;
    cout << setfill('0') << setw(2) << goal.minute << ":";
    cout << setfill('0') << setw(2) << goal.second;
    return cout;
}

istream & operator>>(istream & cin, Time& goal){ // input
    if(goal.second < 0 || goal.minute < 0 || goal.day < 0 || goal.hour < 0){ // error checking
        goal.second = 0, goal.minute = 0, goal.hour = 0, goal.day = 0;
        cout << "At least one input value is less than 0, default the Time object to represent 0." << endl;
    
    }
    else{
        // simplify the object to the appropriate representation.
        while(goal.second >= 60){
            goal.second -= 60;
            goal.minute++;
        }
        while(goal.minute >= 60){
            goal.minute -= 60;
            goal.hour++;
        }
        while(goal.hour >= 24){
            goal.hour -= 24;
            goal.day++;
        }
    }
    return cin;
}

Time operator+(const Time &a, const Time &b){ // addition 

    Time result;
    result.second = a.second + b.second;
    result.minute = a.minute + b.minute;
    result.hour = a.hour + b.hour;
    result.day = a.day + b.day;

    // simplify the object to the appropriate representation.
    while(result.second >= 60){
        result.second -= 60;
        result.minute++;
    }
    while(result.minute >= 60){
        result.minute -= 60;
        result.hour++;
    }
    while(result.hour >= 24){
        result.hour -= 24;
        result.day++;
    }
    return result;
}

Time operator-(const Time &a, const Time &b){ // substraction

    Time result;
    result.second = a.second;
    result.minute = a.minute;
    result.hour = a.hour;
    result.day = a.day;

    if(result.second < b.second){
        result.second += 60;
        result.minute -= 1;
    }
    if(result.minute < b.minute){
        result.minute += 60;
        result.hour -= 1;
    }
    if(result.hour < b.hour){
        result.hour += 60;
        result.day -= 1;
    }
    if(result.day < b.day){
        result.second = 0, result.minute = 0, result.hour = 0, result.day = 0;
        cout << "(The first quantity of time is less than the second, set Time as 0) ";
        return result;
    }
    result.second -= b.second;
    result.minute -= b.minute;
    result.hour -= b.hour;
    result.day -= b.day;
    return result;
}

bool Time::operator==(const Time& goal) const{ // check if the time is equal to another
    if(second != goal.second || minute != goal.minute)
        return false;
    if(hour != goal.hour || day != goal.day)
        return false;
    return true;
}

bool Time::operator!=(const Time& goal) const{ // check if the time is not equal to another
    if(second != goal.second || minute != goal.minute)
        return true;
    if(hour != goal.hour || day != goal.day)
        return true;
    return false;
}

bool Time::operator<=(const Time& goal) const{ // check if the time is equal to or less than another
    int value = 0;
    if(second < goal.second)
        value = 1;
    if(minute - value < goal.minute)
        value = 1;
    if(minute - value >= goal.minute)
        value = 0;
    if(hour - value < goal.hour)
        value = 1;
    if(hour - value >= goal.hour)
        value = 0;
    if(day - value <= goal.day)
        return true;
    return false;
}

bool Time::operator>=(const Time& goal) const{ // check if the time is equal to or more than another
    int value = 0;
    if(second < goal.second)
        value = 1;
    if(minute - value < goal.minute)
        value = 1;
    if(minute - value >= goal.minute)
        value = 0;
    if(hour - value < goal.hour)
        value = 1;
    if(hour - value >= goal.hour)
        value = 0;
    if(day - value >= goal.day)
        return true;
    return false;
}

bool Time::operator>(const Time& goal) const{ // check if the time is more than another
    if(*this >= goal && *this != goal)
        return true;
    return false;
}

bool Time::operator<(const Time& goal) const{ // check if the time is less than another
    if(*this <= goal && *this != goal)
        return true;
    return false;
}

Time& Time::operator++(){ // the second of time = time + 1;
    second++;
    while(second >= 60){ 
        second -= 60;
        minute++;
    }
    while(minute >= 60){
        minute -= 60;
        hour++;
    }
    while(hour >= 24){
        hour -= 24;
        day++;
    }
    return *this;
}

Time Time::operator++(int){ // the second of time = time + 1;
    Time goal = (*this);
    ++(this->second);
    //goal.second++;
    while(second >= 60){ 
        second -= 60;
        minute++;
    }
    while(minute >= 60){
        minute -= 60;
        hour++;
    }
    while(hour >= 24){
        hour -= 24;
        day++;
    }
    return goal;
}

Time& Time::operator--(){ // the second of time = time - 1;
    if(second == 0 && minute == 0 && hour == 0 && day == 0){
        cout << "(the Time object is already at 0, then decrement does not change it) ";
        return *this;
    }
    second--;
    if(second < 0){
        second += 60;
        minute--;
    }
    if(minute < 0){
        minute += 60;
        hour--;
    }

    if(hour < 0){
        hour += 24;
        day--;
    }
    return *this;
}

Time Time::operator--(int){ // the second of time = time - 1;
    Time goal = (*this);
    if(goal.second == 0 && goal.minute == 0 && goal.hour == 0 && goal.day == 0){
        cout << "(the Time object is already at 0, then decrement does not change it) ";
        return *this;
    }
    --(this->second);
    if(second < 0){
        second += 60;
        minute--;
    }
    if(minute < 0){
        minute += 60;
        hour--;
    }

    if(hour < 0){
        hour += 24;
        day--;
    }
    return goal;
}