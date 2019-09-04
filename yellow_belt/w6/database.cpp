//
// Created by dkushn on 28.08.19.
//

#include <set>
#include <string>
#include <ostream>
#include <utility>

#include "date.h"
#include "database.h"


void Database::Add(const Date& date, const string& event){
    auto events_at_date = events.find(date);
    if ( events_at_date != events.end() ){
        if ( find(events_at_date->second.begin(), events_at_date->second.end(), event) == events_at_date->second.end()){
            events[date].emplace_back(event);  // do not add if it is present
        }
    } else {
        events[date].emplace_back(event);
    }
}

bool Database::DeleteEvent(const Date& date, const string& event){
    bool erased{false};
    auto events_at_date = events.find(date);
    if (events_at_date != events.end()){
        auto iter_on_event = find(events_at_date->second.begin(), events_at_date->second.end(), event);
        if(iter_on_event != events_at_date->second.end()){
            events_at_date->second.erase(iter_on_event);
            erased = true;
        }
    }
    return erased;
}


int  Database::DeleteDate(const Date& date){
    int n_deleted_elements{0};
    if (events.find(date) != events.end()){
        n_deleted_elements = events.at(date).size();
        events.erase(date);
    }
    return n_deleted_elements;
}

//vector<string> Database::Find(const Date& date) const{
//    if (events.find(date) != events.end()){
//        return events.at(date);
//    } else {
//        return vector<string>();
//    }
//}

pair<Date,string> Database::Last(const Date &d) const{
    auto upperBound = events.upper_bound(d);

    if (upperBound == events.begin()) {
        throw invalid_argument("");
    }

    auto result = std::prev(upperBound);
    return {result->first, result->second.back()};

//    std::stringstream os;

//    os << result->first << " " << result-> second.back();
//    return os.str();

//    auto pd = make_pair<const Date, set<string>>((const Date &&) d, {});
//    auto last_up_to_date = lower_bound(events.rbegin(), events.rend(), pd, [](const auto &lhs, const auto &rhs){ return lhs.first > rhs.first;});
//    if (last_up_to_date != events.rend()){
//        return  {last_up_to_date->first, last_up_to_date->second.back()}; // FIXME !!! have to use vector instead of set...
//    } else {
//        throw invalid_argument("");
//    }
}

void Database::Print(ostream &os) const{
    for (const auto &date_events: events){
        for (const auto& event: date_events.second){
            os << date_events.first << ' ' << event << endl;
        }
    }
}

void Database::ExecuteCommandLine(const string& command_line) {
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
                Add(date_buf, event_name);
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
                Print(cout);
                break;
            case (cFind):
//                line_stream >> date_buf;
//                cout << Find(date_buf);
                break;
        }
    }

}

ostream& operator<<(ostream& os, const pair<Date,string> &p){
    os << p.first << ' ' << p.second ;
    return os;
}

ostream& operator<<(ostream& os, const pair<Date,set<string>> &p){
        for( const auto& event_in_day: p.second){
            os << p.first << ' ' << event_in_day;
        }
    return os;
}



