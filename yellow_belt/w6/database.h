//
// Created by dkushn on 28.08.19.
//

#pragma once


#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include "date.h"
#include <functional>

using namespace std;

class Database {

    map<Date,set<string>> events_;
    map<Date,vector<string>> history_;

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


    void Add(const Date& date, const string& event);

    bool DeleteEvent(const Date& date, const string& event);

    int  DeleteDate(const Date& date);


    void Print(ostream &os) const;

    pair<Date,string> Last(const Date &d) const;

//    template <typename Predicate>
    int RemoveIf(const std::function<bool(Date, string)> &p) {
        int removed_els{0};
        vector<Date> empty_keys;
        for (auto &pair: history_) {

            auto remove_it = stable_partition( pair.second.begin(), pair.second.end(),
                    [p, pair](const auto &el){ return !p(pair.first, el);}
                    );

            removed_els += distance(remove_it, pair.second.end());

            for(auto event_to_remove = remove_it; event_to_remove != pair.second.end(); event_to_remove = next(event_to_remove)){
                events_[pair.first].erase(*event_to_remove);
            }

            pair.second.erase(remove_it, pair.second.end());


            if (pair.second.empty()){
                empty_keys.emplace_back(pair.first);
            }
        }

        for(const auto& empty_key: empty_keys){
            history_.erase(empty_key);
            events_.erase(empty_key);
        }


        return removed_els;
    }

    vector<pair<Date,string>> FindIf(const std::function<bool(Date, string)> &p) const
    {
        vector<pair<Date,string>> results;
        for (const auto &pair: history_){
            for(auto find_it = find_if( pair.second.begin(), pair.second.end(),
                                        [p, pair](const string& event_name){
                                            return p(pair.first, event_name);});
            find_it != pair.second.end();
            find_it = find_if( next(find_it), pair.second.end(),
                            [p, pair](const string& event_name){
                                return p(pair.first, event_name);
                            })
                                    ){
                results.emplace_back(pair.first, *find_it);
            }
        }
        return results;
    }

    void ExecuteCommandLine(const string& command_line);

};

ostream& operator<<(ostream& os, const pair<Date,string> &p);
ostream& operator<<(ostream& os, const pair<Date,set<string>> &p);

