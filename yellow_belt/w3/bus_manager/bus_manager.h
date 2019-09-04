//
// Created by dkushn on 14.08.19.
//

#ifndef CPP_BELTS_BUS_MANAGER_H
#define CPP_BELTS_BUS_MANAGER_H

#include <string>
#include <vector>
#include "responses.h"

using namespace std;

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops);

    BusesForStopResponse GetBusesForStop(const string& stop) const;

    StopsForBusResponse GetStopsForBus(const string& bus) const;

    AllBusesResponse GetAllBuses() const ;

private:
    map<string, vector<string>> stop_to_bus;
    map<string, vector<string>> bus_to_stops;
};


#endif //CPP_BELTS_BUS_MANAGER_H
