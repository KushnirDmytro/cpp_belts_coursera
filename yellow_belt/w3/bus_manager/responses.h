//
// Created by dkushn on 14.08.19.
//

#ifndef CPP_BELTS_RESPONSES_H
#define CPP_BELTS_RESPONSES_H

#include <vector>
#include <string>
#include <map>
#include <iostream>

using namespace std;



    struct BusesForStopResponse {
        string stop_name;
        vector<string> buses;
        // Наполните полями эту структуру
    };

struct StopsForBusResponse {
    vector< pair<string, vector<string>> > stops_interchange;
};

    struct AllBusesResponse {
        map<string, vector<string>> buses;
    };

template <typename T>
    ostream& operator << (ostream& os, const vector<T>& v){
    bool first = true;
    for (const auto& el: v){
        if (first){
            os << el;
            first = false;
        } else {
            os << ' ' << el;
        }
    }
    return os;
    }


ostream& operator << (ostream& os, const BusesForStopResponse& r);

ostream& operator << (ostream& os, const StopsForBusResponse& r);

ostream& operator << (ostream& os, const AllBusesResponse& r);



#endif //CPP_BELTS_RESPONSES_H
