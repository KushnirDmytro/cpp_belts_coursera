//
// Created by dkushn on 28.08.19.
//
#pragma once

#include <iostream>
#include <sstream>
#include <set>

using namespace std;

class Date {
    int year;
    int month;
    int day;
public:
    Date():year{0},month{0},day{0}{
    }

    Date(int new_year, int new_month, int new_day);

    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;

    friend istream& operator>>(istream& is, Date& d);
};

bool operator<(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator==(const Date&lhs, const Date&rhs);
bool operator!=(const Date&lhs, const Date&rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);

Date ParseDate(istream &is);
ostream& operator<<(ostream& os,const Date& d);
ostream& operator<<(ostream& os,const set<string>& d);
