//
// Created by dkushn on 21.07.19.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <map>
using namespace std;

/*
 in:
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


 out:
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




//Реализуйте систему хранения автобусных маршрутов. Вам нужно обрабатывать следующие запросы:
//
//NEW_BUS bus stop_count stop1 stop2 ... — добавить маршрут автобуса с названием bus и stop_count остановками с названиями stop1, stop2, ...
//BUSES_FOR_STOP stop — вывести названия всех маршрутов автобуса, проходящих через остановку stop.
//STOPS_FOR_BUS bus — вывести названия всех остановок маршрута bus со списком автобусов, на которые можно пересесть на каждой из остановок.
//ALL_BUSES — вывести список всех маршрутов с остановками.
//Формат ввода
//В первой строке ввода содержится количество запросов Q, затем в Q строках следуют описания запросов.
//
//Гарантируется, что все названия маршрутов и остановок состоят лишь из латинских букв, цифр и знаков подчёркивания.
//
//Для каждого запроса NEW_BUS bus stop_count stop1 stop2 ... гарантируется, что маршрут bus отсутствует, количество остановок больше 0,
// а после числа stop_count следует именно такое количество названий остановок, причём все названия в каждом списке различны.
//
//Формат вывода
//Для каждого запроса, кроме NEW_BUS, выведите соответствующий ответ на него:
//
//На запрос BUSES_FOR_STOP stop выведите через пробел список автобусов,
// проезжающих через эту остановку, в том порядке, в котором они создавались командами NEW_BUS.
// Если остановка stop не существует, выведите No stop.
//
// На запрос STOPS_FOR_BUS bus выведите описания остановок маршрута bus в отдельных строках в том порядке,
// в котором они были заданы в соответствующей команде NEW_BUS.
// Описание каждой остановки stop должно иметь вид
// Stop stop: bus1 bus2 ..., где bus1 bus2 ... — список автобусов, проезжающих через остановку stop, в порядке, в котором они создавались командами NEW_BUS,
// за исключением исходного маршрута bus.
// Если через остановку stop не проезжает ни один автобус, кроме bus, вместо списка автобусов для неё выведите no interchange. Если маршрут bus не существует, выведите No bus.
//
// На запрос ALL_BUSES выведите описания всех автобусов в алфавитном порядке. Описание каждого маршрута bus должно иметь вид Bus bus: stop1 stop2 ..., где stop1 stop2 ... — список остановок автобуса bus в порядке, в котором они были заданы в соответствующей команде NEW_BUS. Если автобусы отсутствуют, выведите No buses.
//Предупреждение
//Условие задачи выше содержит много важных деталей. Если вы не уверены в том, что не упустили ни одной, перечитайте условие ещё раз.

template<class T> ostream& operator<<(ostream& os, vector<T> v){
    for (const auto &s: v){
        cout << s << " ";
    }
    return os;
}

template <class K, class V> ostream& operator <<(ostream& os, const map<K,V> &m){
    for (const auto& item: m){
        cout << item.first << "/" << item.second << " ";
    }
    return os;
}


enum commands{
    NEW_BUS, BUSES_FOR_STOP, STOPS_FOR_BUS, ALL_BUSES
};

map<string, commands> known_commands{
        {"NEW_BUS", NEW_BUS},
        {"BUSES_FOR_STOP",BUSES_FOR_STOP},
        {"STOPS_FOR_BUS",STOPS_FOR_BUS},
        {"ALL_BUSES", ALL_BUSES}
};

int main() {


    int Q;
    cin >> Q;
    string A, B;
    string command;

    map<string, vector<string>> b2s; // bus-to-route
    map<string, vector<string>> s2b; // route-to-bus

    for (int i = 0; i < Q; ++i){
        cin >> command;
        commands com = known_commands[command];

        switch (com){
            case NEW_BUS:{
                string bus;
                cin >> bus;
                int stops_n;
                cin >> stops_n;
                b2s[bus] = vector<string>(stops_n);
                for(string &stop_name: b2s[bus]){
                    cin >> stop_name;
                    s2b[stop_name].push_back(bus); // todo is there guarantee that bus mets only once?
                }
            }
                break;
            case BUSES_FOR_STOP:{
                string stop;
                cin >> stop;
                if (s2b.count(stop) == 0){
                    cout << "No stop" << endl;
                }
                else{
                    cout << s2b[stop] << endl;
                }
            }
                break;
            case STOPS_FOR_BUS:{
                string bus;
                cin >> bus;
                if (b2s.count(bus) == 0){
                    cout << "No bus" << endl;
                }
                else{
                    for (const string& stop_on_route: b2s[bus]){
                        cout << "Stop " << stop_on_route << ": ";
                        if (s2b[stop_on_route].size() == 1){
                            cout << "no interchange" << endl;
                        }
                        else{
                            for (const string &bus_on_stop: s2b[stop_on_route]){
                                if (bus_on_stop != bus){
                                    cout << bus_on_stop << " ";
                                }
                            }
                            cout << endl;
                        }
                    }
                }
            }
                break;

            case ALL_BUSES:{
                if(b2s.empty()){
                    cout << "No buses" << endl;
                }
                else{
                    for (const auto &bus_info: b2s){
                        cout << "Bus " << bus_info.first << ":" << " ";
                        cout << bus_info.second;
                        cout << endl;
                    }
                }
            }
                break;
        }
    }

}
