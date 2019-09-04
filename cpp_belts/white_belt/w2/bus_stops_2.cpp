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
4
2 Marushkino Kokoshkino
1 Kokoshkino
2 Marushkino Kokoshkino
2 Kokoshkino Marushkino


 out:
New bus 1
New bus 2
Already exists for 1
New bus 3

 */




//В этой задаче вам нужно присваивать номера автобусным маршрутам.
//
//А именно, для каждого маршрута, заданного набором названий остановок, нужно либо выдать новый номер (первому маршруту — 1, второму — 2 и т. д.),
// либо вернуть номер существующего маршрута, которому соответствует такой набор остановок.
//
//Наборы остановок, полученные друг из друга перестановкой остановок, считаются различными (см. пример).
//
//Указание
//В C++ ключом словаря может быть не только число или строка, но и другой контейнер, например, vector.
//
//Формат ввода
//Сначала вводится количество запросов Q, затем Q описаний запросов.
//
//Каждый запрос представляет собой положительное количество остановок N,
// за которым следуют разделённые пробелом N различных названий остановок соответствующего маршрута.
// Названия остановок состоят лишь из латинских букв и символов подчёркивания.
//
//Формат вывода
//Выведите ответ на каждый запрос в отдельной строке.
//
//Если маршрут с данным набором остановок уже существует, в ответ на соответствующий запрос выведите
// Already exists for i, где i — номер маршрута с таким набором остановок.
// В противном случае нужно выделить введённому набору остановок новый номер i и вывести его в формате New bus i.


int main() {


    int Q, N;
    cin >> Q;

    map<vector<string>, int> r2b; // route-to-bus
    map<int, vector<string>> b2r; // bus-2-route

    for (int i = 0; i < Q; ++i) {
        cin >> N;
        vector<string> reading_stops(N);
        for (string &stop: reading_stops) {
            cin >> stop;
        }
        if (r2b.count(reading_stops) != 0) {
            cout << "Already exists for " << r2b[reading_stops] << endl;
        } else {
            int size_buf = r2b.size();
            r2b[reading_stops] = size_buf + 1;
            cout << "New bus " << size_buf + 1 << endl;
        }
    }

}
