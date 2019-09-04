#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;


enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

map <string, QueryType> known_queries{
        {"NEW_BUS", QueryType ::NewBus},
        {"BUSES_FOR_STOP", QueryType ::BusesForStop},
        {"STOPS_FOR_BUS", QueryType ::StopsForBus},
        {"ALL_BUSES", QueryType ::AllBuses}
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
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

struct BusesForStopResponse {
    string stop_name;
    vector<string> buses;
    // Наполните полями эту структуру
};

ostream& operator << (ostream& os, const vector<string>& v){
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

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.stop_name.empty()){
        os << "No stop";
    } else {
        os << r.buses;
    }
    return os;
}

struct StopsForBusResponse {
    vector< pair<string, vector<string>> > stops_interchange;
};


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

struct AllBusesResponse {
    map<string, vector<string>> buses;
};
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


class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        bus_to_stops[bus] = vector<string>(stops);
        for (const auto &stop: stops){
            stop_to_bus[stop].emplace_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        if (stop_to_bus.find(stop) != stop_to_bus.end())
            return {stop, stop_to_bus.at(stop)};
        else
            return {"", {}};
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
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

    AllBusesResponse GetAllBuses() const {
        return {bus_to_stops};
    }

private:
    map<string, vector<string>> stop_to_bus;
    map<string, vector<string>> bus_to_stops;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }

    return 0;
}

/*


int main_2() {
    int q;
    cin >> q;

    map<string, vector<string>> buses_to_stops, stops_to_buses;

    for (int i = 0; i < q; ++i) {
        string operation_code;
        cin >> operation_code;

        if (operation_code == "NEW_BUS") {

            string bus;
            cin >> bus;
            int stop_count;
            cin >> stop_count;
            vector<string>& stops = buses_to_stops[bus];
            stops.resize(stop_count);
            for (string& stop : stops) {
                cin >> stop;
                stops_to_buses[stop].push_back(bus);
            }

        } else if (operation_code == "BUSES_FOR_STOP") {

            string stop;
            cin >> stop;
            if (stops_to_buses.count(stop) == 0) {
                cout << "No stop" << endl;
            } else {
                for (const string& bus : stops_to_buses[stop]) {
                    cout << bus << " ";
                }
                cout << endl;
            }

        } else if (operation_code == "STOPS_FOR_BUS") {

            string bus;
            cin >> bus;
            if (buses_to_stops.count(bus) == 0) {
                cout << "No bus";
            } else {
                for (const string& stop : buses_to_stops[bus]) {
                    cout << "Stop " << stop << ": ";
                    if (stops_to_buses[stop].size() == 1) {
                        cout << "no interchange";
                    } else {
                        for (const string& other_bus : stops_to_buses[stop]) {
                            if (bus != other_bus) {
                                cout << other_bus << " ";
                            }
                        }
                    }
                }
            }

        } else if (operation_code == "ALL_BUSES") {

            if (buses_to_stops.empty()) {
                cout << "No buses";
            } else {
                for (const auto& bus_item : buses_to_stops) {
                    cout << "Bus " << bus_item.first << ": ";
                    for (const string& stop : bus_item.second) {
                        cout << stop << " ";
                    }
                }
            }

        }
    }

    return 0;
}
*/


/*
 10
ALL_BUSES
BUSES_FOR_STOP Marushkino
STOPS_FOR_BUS 32K
NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo
NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo
BUSES_FOR_STOP Vnukovo
NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo
NEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo
STOPS_FOR_BUS 272
ALL_BUSES

 */

/*
No buses
No stop
No bus
32 32K
Stop Vnukovo: 32 32K 950
Stop Moskovsky: no interchange
Stop Rumyantsevo: no interchange
Stop Troparyovo: 950
Bus 272: Vnukovo Moskovsky Rumyantsevo Troparyovo
Bus 32: Tolstopaltsevo Marushkino Vnukovo
Bus 32K: Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo
Bus 950: Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo
 */