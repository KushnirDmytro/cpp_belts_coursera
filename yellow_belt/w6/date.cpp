//
// Created by dkushn on 28.08.19.
//

#include <iostream>
#include <iomanip>
#include <set>

#include "date.h"

//using namespace std;


    Date::Date(const int new_year, const int new_month, const int new_day)
    : year{new_year}, month{new_month}, day{new_day}
    {
        if (new_month < 1 || new_month > 12)
            throw invalid_argument("Month value is invalid: " + to_string(new_month));
        if (new_day < 1 || new_day > 31 )
            throw invalid_argument("Day value is invalid: " + to_string(new_day));
//        year = new_year;
//        month = new_month;
//        day = new_day; // todo check if can use init list here
    }

    int Date::GetYear() const{
        return year;
    }
    int Date::GetMonth() const{
        return month;
    }
    int Date::GetDay() const{
        return day;
    }



bool operator==(const Date&lhs, const Date&rhs){
    return (lhs.GetYear() == rhs.GetYear()) && (lhs.GetMonth() == rhs.GetMonth()) && (lhs.GetDay() == rhs.GetDay());
}

bool operator!=(const Date&lhs, const Date&rhs){ return !(lhs == rhs);}


bool operator<(const Date& lhs, const Date& rhs){
    if (lhs.GetYear() != rhs.GetYear()) {
        return lhs.GetYear() < rhs.GetYear();
    }
    else {
        if (lhs.GetMonth() != rhs.GetMonth()){
            return lhs.GetMonth() < rhs.GetMonth();
        }
        else{
            return  (lhs.GetDay() < rhs.GetDay());
        }
    }
}

bool operator<=(const Date& lhs, const Date& rhs){
    return lhs < rhs || lhs == rhs;
}

bool operator>(const Date& lhs, const Date& rhs){
    return !(lhs <= rhs);
}

bool operator>=(const Date& lhs, const Date& rhs){
    return !(lhs < rhs);
}


istream& operator>>(istream& is, Date& d){
    int buf_year, buf_month, buf_day;
    string string_date;
    is >> string_date;
    stringstream string_date_stream(string_date);

    string_date_stream >> buf_year;
    if (string_date_stream.peek() != '-')
        throw invalid_argument( "Wrong date format: " + string_date );
    string_date_stream.ignore(1, '-');
    string_date_stream >> buf_month;
    if (string_date_stream.peek() != '-')
        throw invalid_argument( "Wrong date format: " + string_date );
    string_date_stream.ignore(1, '-');
    if ( !(string_date_stream >> buf_day) )
        throw invalid_argument( "Wrong date format: " + string_date );
    if (!string_date_stream.eof())
        throw invalid_argument( "Wrong date format: " + string_date );
    else {
        d = Date(buf_year, buf_month, buf_day);
    }
    return is;
}

Date ParseDate(istream &is){
        Date d;
        is >> d;
        return d;
    }


ostream& operator<<(ostream& os,const Date& d){
    os << setw(4) << setfill('0') << d.GetYear() << '-' <<
       setw(2) << d.GetMonth() << '-' <<
       setw(2) << d.GetDay();
    return os;
}

ostream& operator<<(ostream& os,const set<string>& d){
    size_t i = 0;
    for(const auto& el: d){
        cout << el << endl;
    }
    return os;
}
