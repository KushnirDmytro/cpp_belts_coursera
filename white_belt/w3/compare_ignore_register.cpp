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
stdin	stdout
2 q A	A q
3 a C b	a b C
 */




//Условие
//В стандартном потоке дана одна строка, состоящая из числа N и следующих за ним N строк S. Между собой число и строки разделены пробелом.
//
//Отсортируйте строки S в лексикографическом порядке по возрастанию, игнорируя регистр букв, и выведите их в стандартный поток вывода.
//
//Ограничения
//0 <= N <= 1000
//1 <= |S| <= 15
//Каждая строка S[i] может состоять из следующих символов: [0-9,a-z,A-Z]



template<class T> ostream& operator<<(ostream& os, vector<T> v){
    for (const auto &s: v){
        cout << s << " ";
    }
    return os;
}

int main() {
    int N;
    cin >> N;
    vector<string> to_sort(N);
    for (auto &el: to_sort){
        cin >> el;
    }
    sort(to_sort.begin(), to_sort.end(), [](string l, string r){
        char lower_l[l.size()], lower_r[r.size()];
        for(int i = 0; i < l.size(); ++i){
            lower_l[i] = tolower(l[i]);
        }
        for(int i = 0; i < r.size(); ++i){
            lower_r[i] = tolower(r[i]);
        }
        return string(lower_l) < string(lower_r);
    });
    cout << to_sort << endl;
}
