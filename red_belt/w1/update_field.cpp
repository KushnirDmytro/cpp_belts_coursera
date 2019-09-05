#include "airline_ticket.h"
#include "test_runner.h"

using namespace std;

#define UPDATE_FIELD(ticket, field, values) \
if (values.find(#field) != values.end())       \
    stringstream(values.at(#field)) >> ticket.field ;
// Реализуйте этот макрос, а также необходимые операторы для классов Date и Time



ostream& operator<<(ostream& os, const Date &d){
    os << d.year << "-" << d.month << "-" << d.day;
    return os;
}

ostream& operator<<(ostream& os, const Time &d){
    os << d.hours << "-" << d.minutes;
    return os;
}


istream& operator>>(istream& is,  Date &d){
    is >> d.year;
    is.ignore(1, '-');
    is >> d.month;
    is.ignore(1, '-');
    is >> d.day;
    return is;
}

istream& operator>>(istream& is,  Time &d){
    is >> d.hours;
    is.ignore(1, ':');
    is >> d.minutes;
    return is;
}


bool operator<(const Date &lhs, const Date &rhs){
    return vector<int>{lhs.year, lhs.month, lhs.day} < vector<int>{rhs.year, rhs.month, rhs.day};
}

bool operator==(const Date &lhs, const Date &rhs){
    return vector<int>{lhs.year, lhs.month, lhs.day} == vector<int>{rhs.year, rhs.month, rhs.day};
}

bool operator<(const Time &lhs, const Time &rhs){
    return vector<int>{lhs.hours, lhs.minutes} < vector<int>{rhs.hours, rhs.minutes};
}

bool operator==(const Time &lhs, const Time &rhs){
    return vector<int>{lhs.hours, lhs.minutes} == vector<int>{rhs.hours, rhs.minutes};
}

void TestUpdate() {
  AirlineTicket t;
  t.price = 0;

  const map<string, string> updates1 = {
    {"departure_date", "2018-2-28"},
    {"departure_time", "17:40"},
  };
  UPDATE_FIELD(t, departure_date, updates1);
  UPDATE_FIELD(t, departure_time, updates1);
  UPDATE_FIELD(t, price, updates1);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 0);

  const map<string, string> updates2 = {
    {"price", "12550"},
    {"arrival_time", "20:33"},
  };
  UPDATE_FIELD(t, departure_date, updates2);
  UPDATE_FIELD(t, departure_time, updates2);
  UPDATE_FIELD(t, arrival_time, updates2);
  UPDATE_FIELD(t, price, updates2);

  // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
  // значения этих полей не должны измениться
  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 12550);
  ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestUpdate);
}
