//
// Created by dkushn on 21.07.19.
//

//
// Created by dkushn on 21.07.19.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
using namespace std;

/*
 in:
8
ADD program code
COUNT cipher
ADD code cipher
COUNT code
COUNT program
CHECK code program
CHECK program cipher
CHECK cpp java


 out:
0
2
1
YES
NO
NO

 */


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
5
2 Marushkino Kokoshkino
1 Kokoshkino
2 Marushkino Kokoshkino
2 Kokoshkino Marushkino
2 Kokoshkino Kokoshkino


 out:
New bus 1
New bus 2
Already exists for 1
Already exists for 1
Already exists for 2

 */




//В этой задаче вам нужно присваивать номера автобусным маршрутам.
//
//А именно, для каждого маршрута, заданного множеством названий остановок, нужно либо выдать новый номер
// (первому маршруту — 1, второму — 2 и т. д.), либо вернуть номер существующего маршрута, которому соответствует такое множество остановок.
//
//В отличие от задачи «Автобусные остановки — 2», наборы остановок, которые можно получить друг из друга перестановкой
// элементов или добавлением/удалением повторяющихся, следует считать одинаковыми.
//
//Формат ввода
//Сначала вводится количество запросов Q, затем Q описаний запросов.
//
//Каждый запрос представляет собой положительное количество остановок N, за которым следуют разделённые пробелом
// N названий остановок соответствующего маршрута (не обязательно различных).
// Названия остановок состоят лишь из латинских букв и символов подчёркивания.
//
//Формат вывода
//Выведите ответ на каждый запрос в отдельной строке.
//
//Если маршрут с данным набором остановок уже существует, в ответ на соответствующий запрос выведите Already exists for i,
//где i — номер маршрута с таким набором остановок. В противном случае нужно выделить введённому набору остановок новый номер i и вывести его в формате New bus i.

//

int main() {


    int Q, N;
    cin >> Q;

    map<set<string>, int> r2b; // route-to-bus
    map<int, set<string>> b2r; // bus-2-route

    for (int i = 0; i < Q; ++i) {
        cin >> N;
        set<string> reading_stops;
        string s_buf;
        for (int j = 0; j < N; ++j) {
            cin >> s_buf;
            reading_stops.insert(s_buf);
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
