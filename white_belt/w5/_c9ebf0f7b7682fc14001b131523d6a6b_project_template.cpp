#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <set>
#include <iomanip>

using namespace std;
// Реализуйте функции и методы классов и при необходимости добавьте свои

class Date {
    int year;
    int month;
    int day;
public:
    Date():year{0},month{0},day{0}{
    }

    Date(const int new_year, const int new_month, const int new_day){
        if (new_month < 1 || new_month > 12)
            throw invalid_argument("Month value is invalid: " + to_string(new_month));
        if (new_day < 1 || new_day > 31 )
            throw invalid_argument("Day value is invalid: " + to_string(new_day));
        year = new_year;
        month = new_month;
        day = new_day; // todo check if can use init list here
    }

    int GetYear() const{
        return year;
    }
    int GetMonth() const{
        return month;
    }
    int GetDay() const{
        return day;
    }
    friend istream& operator>>(istream& is, Date& d);
};

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

bool operator==(const Date&lhs, const Date&rhs){
    return (lhs.GetYear() == rhs.GetYear()) && (lhs.GetMonth() == rhs.GetMonth()) && (lhs.GetDay() == rhs.GetDay());
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

class Database {
    map<Date,set<string>> events;


    enum commands{
        cAdd, cDel, cPrint, cFind
    };

    const map<string, commands> command_decoder{
            {"Add", cAdd},
            {"Del", cDel},
            {"Print", cPrint},
            {"Find", cFind}
    };

public:


    void AddEvent(const Date& date, const string& event){
        events[date].insert(event);
    }

    bool DeleteEvent(const Date& date, const string& event){
        bool erased{false};
        if (events.find(date) != events.end()){
            auto event_position = events.at(date).find(event);
            if(events.at(date).find(event) != events.at(date).end()){
                events.at(date).erase(event_position);
                erased = true;
            }
            if (events.at(date).empty()){
                events.erase(date);
            }
        }
        return erased;
    }


    int  DeleteDate(const Date& date){
        int n_deleted_elements{0};
        if (events.find(date) != events.end()){
            n_deleted_elements = events.at(date).size();
            events.erase(date);
        }
        return n_deleted_elements;
    }

    set<string> Find(const Date& date) const{
        if (events.find(date) != events.end()){
            return events.at(date);
        } else {
            return set<string>();
        }
    }

    void Print() const{
        for (const auto &date_events: events){
            for (const auto& event: date_events.second){
                cout << date_events.first << ' ' << event << endl;
            }
        }
    }

    void ExecuteCommandLine(const string& command_line) {
        string str_cmd;

        stringstream line_stream(command_line);
        line_stream >> str_cmd;
        if (str_cmd.empty())
            return;

        if (command_decoder.find(str_cmd) == command_decoder.end()){
            throw invalid_argument("Unknown command: " + str_cmd);
        }
        else{
            commands decoded_command = command_decoder.at(str_cmd);
            Date date_buf;
            string event_name;
            switch (decoded_command) {
                case (cAdd):
                    line_stream >> date_buf >> event_name;
                    AddEvent(date_buf, event_name);
                    break;
                case (cDel):
                    line_stream >> date_buf;
                    if (line_stream.eof()) {
                        int n_deleted = DeleteDate(date_buf);
                        cout << "Deleted " << n_deleted << " events" << endl;
                    } else {
                        line_stream >> event_name;
                        string msg;
                        msg = DeleteEvent(date_buf, event_name) ? "Deleted successfully" : "Event not found";
                        cout << msg << endl;
                    }
                    break;
                case (cPrint):
                    Print();
                    break;
                case (cFind):
                    line_stream >> date_buf;
                    cout << Find(date_buf);
                    break;
            }
        }

    }

};


int main() {
    Database db;
    string line_buf, command_string, event_name;
    try {
        while (getline(cin, line_buf)) {
            if (line_buf.empty()){
                continue;
            }
            db.ExecuteCommandLine(line_buf);
        }
    }
    catch (exception &e){
        cout << e.what() << endl;
    }
    return 0;
}

/*
 *
 Add 0-1-2 event1
 Add 0-1-2 event0
Add 1-2-3 event2
Find 0-1-2

Del 0-1-2
Print
Del 1-2-3 event2
Del 1-2-3 event2




Add 0-1-2 event1
Add 1-2-3 event2
Find 0-1-2
Del 0-1-2
Print
Del 1-2-3 event2
Del 1---2-3
Del 1-2-3 event2



 * */

/*
 Wrong date format:

Add 1-1-1- event1

Add 1-2-3*ff

Add 1-0 event1

Add 1-0-9- event1

Add 2001-9-0- event1

Add a1-1-1 a

Add a1-1-1a a

Add - event1

Add 0 event1

Month value is invalid:

Add 1-0- event1

Add 1-0-999 event1

Add 1-999-1 event1

Add 1-0-1 a

Add 1--1-1 event1

Add 1--1--1 event1

Day value is invalid:

Add 1-1-0 a

Add 1-1--1 event1

 * */


/*
OK:
Add 1-1-1 task
Add -2-1-1 task
Add 03-01-01 task
Add +4-1-1 task
Add 1-+6-1 task
Add 1-1-+7 task

Wrong date format: DATE
Add f8-1-1 task
Add 9f-1-1 task
Add 1-11f-1 task
Add 1-f12-1 task
Add 1-1-f13 task!
Add 1-1-14f task
Add --15-1-1 task
Add 1---2-1 task
Add 1-1---17 task
Add 1-1- task
Add 1--1 task
Add --111 task
Add 1---+++1 task
Add --++1 task
Add 1-1-f task
Del foo

Month value is invalid: MONTH
Add 1--1-32 task
Add 1-0-32 task
Add 1-13-32 task
Add 1-+0-32 task

Day value is invalid: DAY
Add 1-1--1 task
Add 1-1-0 task
Add 1-1-+0 task
Add 1-1-32 task



Add 1-1-1 task
Find 2-2-2
Print blah


Skipped
<Empty cin>
Add 1-1-1
Add task
Find <Not existing but correct date>
Print <Any additional string>

Unknown command: FIRSTWORD
<Any first string except Add, Del, Find, Print>
add 1-1-1 task
Scrum 1-16-93 today

 Add 1-1-1 C
Add 1-1-1 A
Add 1-1-1 B
Add 1-2-1 task2
Add 1-1-2 task3
Add 2-1-1 task1
Print


Sorting:
Input:
Add 1-1-1 C
Add 1-1-1 A
Add 1-1-1 B
Add 1-2-1 task2
Add 1-1-2 task3
Add 2-1-1 task1
Output:
0001-01-01 A
0001-01-01 B
0001-01-01 C
0001-01-02 task3
0001-02-01 task2
0002-01-01 task1

Input:
Find 1-1-1
Output:
A
B
C


Add 1-1-1 C
Add 1-1-1 A
Add 1-1-1 B
Add 1-2-1 task2
Add 1-1-2 task3
Add 2-1-1 task1
Find 1-1-1



 * */