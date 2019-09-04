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
2 -4 3	3 -4
3 1 -3 2	1 2 -3
 */




//Условие
//В стандартном потоке дана одна строка, состоящая из N + 1 целых чисел. Первым числом идёт само число N. Далее следуют ещё N чисел, обозначим их за массив A. Между собой числа разделены пробелом.
//
//Отсортируйте массив А по модулю и выведите его в стандартный поток.
//
//Ограничения
//0 <= N <= 1000
//-1000000 <= A[i] <= 1000000
//



template<class T> ostream& operator<<(ostream& os, vector<T> v){
    for (const auto &s: v){
        cout << s << " ";
    }
    return os;
}

int main() {
    int N;
    cin >> N;
    vector<int> to_sort(N);
    for (auto &el: to_sort){
        cin >> el;
    }
    sort(to_sort.begin(), to_sort.end(), [](int l, int r){ return abs(l) < abs(r);});
    cout << to_sort << endl;
}
