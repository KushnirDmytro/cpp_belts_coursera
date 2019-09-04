//
// Created by dkushn on 14.08.19.
//

#ifndef CPP_BELTS_QUERY_H
#define CPP_BELTS_QUERY_H

#include <string>
#include <vector>
#include <map>

namespace std{

    enum class QueryType {
        NewBus,
        BusesForStop,
        StopsForBus,
        AllBuses
    };


    struct Query {
        QueryType type;
        string bus;
        string stop;
        vector<string> stops;
    };


    istream& operator >> (istream& is, Query& q);



}


#endif //CPP_BELTS_QUERY_H
