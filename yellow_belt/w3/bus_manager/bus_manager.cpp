//
// Created by dkushn on 14.08.19.
//

#include "bus_manager.h"

#include <algorithm>

using namespace std;



    void BusManager::AddBus(const string& bus, const vector<string>& stops) {
        bus_to_stops[bus] = vector<string>(stops);
        for (const auto &stop: stops){
            stop_to_bus[stop].emplace_back(bus);
        }
    }

    BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
        if (stop_to_bus.find(stop) != stop_to_bus.end())
            return {stop, stop_to_bus.at(stop)};
        else
            return {"", {}};
    }

    StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
        StopsForBusResponse response = {};
        if (bus_to_stops.find(bus) == bus_to_stops.end())
            return response;

        for (const auto &stop: bus_to_stops.at(bus)){
            pair<string, vector<string>> new_interchange = {stop, vector<string>{stop_to_bus.at(stop).size() - 1}};
            copy_if(stop_to_bus.at(stop).begin(), stop_to_bus.at(stop).end(), new_interchange.second.begin(),
                    [bus](const string& bus_name){ return bus_name != bus; });
            response.stops_interchange.emplace_back(new_interchange);
        }

        return response;
    }

    AllBusesResponse BusManager::GetAllBuses() const {
        return {bus_to_stops};
    }

