//
// Created by dkushn on 14.08.19.
//

#include "responses.h"

using namespace std;


ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.stop_name.empty()){
        os << "No stop";
    } else {
        os << r.buses;
    }
    return os;
}

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if (r.stops_interchange.empty()){
        os << "No bus";
    } else {
        bool first = true;
        for (const auto& interchange: r.stops_interchange){
            if (!first){
                os << endl;
            }
            first = false;
            os << "Stop " << interchange.first << ": ";
            if (interchange.second.empty())
                os << "no interchange";
            else
                os << interchange.second;
        }
    }
    return os;
}

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (r.buses.empty()){
        os << "No buses";
    } else {
        bool first = true;
        for (const auto &bus_rout: r.buses){
            if (!first){
                os << endl;
            }
            first = false;
            os << "Bus " << bus_rout.first << ": " << bus_rout.second;
        }
    }
    return os;
}