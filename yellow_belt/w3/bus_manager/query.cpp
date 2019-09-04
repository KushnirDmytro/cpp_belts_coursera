//
// Created by dkushn on 14.08.19.
//

#include "query.h"

#include <istream>

namespace std{
    map <string, QueryType> known_queries{
            {"NEW_BUS", QueryType ::NewBus},
            {"BUSES_FOR_STOP", QueryType ::BusesForStop},
            {"STOPS_FOR_BUS", QueryType ::StopsForBus},
            {"ALL_BUSES", QueryType ::AllBuses}
    };


    istream& operator >> (istream& is, Query& q) {
    q = {};
    string str_query_name, bus_id;
    is >> str_query_name;
    q.type = known_queries[str_query_name];
    switch (q.type){
        case (QueryType::NewBus):{
            is >> q.bus;
            size_t stop_count;
            is >> stop_count;
            q.stops = vector<string>(stop_count);
            for (auto &stop: q.stops)
                is >> stop;

            break;
        }
        case (QueryType ::BusesForStop):{
            is >> q.stop;
            break;
        }
        case (QueryType::StopsForBus):{
            is >> q.bus;
            break;
        }
    }
    return is;
}

}