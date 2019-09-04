//
// Created by dkushn on 21.07.19.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


//Даны значения температуры, наблюдавшиеся в течение N подряд идущих дней. Найдите номера дней (в нумерации с нуля)
// со значением температуры выше среднего арифметического за все N дней.
//
//Гарантируется, что среднее арифметическое значений температуры является целым числом.
//
//Формат ввода
//Вводится число N, затем N неотрицательных целых чисел — значения температуры в 0-й, 1-й, ... (N−1)-й день.
//
//Формат вывода
//Первое число K — количество дней, значение температуры в которых выше среднего арифметического.
// Затем K целых чисел — номера этих дней.

/*
 in: 5
7 6 3 0 9
 out:
 3
0 1 4
 */


template<class T> ostream& operator<<(ostream& st, vector<T> v){
    for (auto &s: v){
        cout << s << " ";
    }
    cout << endl;
}

int main() {
    vector<int> temps;
    int N, temp, s{0};

    cin >> N;
    for (int i = 0; i < N; ++i){
        cin >> temp;
        temps.push_back(temp);
        s += temp;
    }

    int mean_temp = s / N;

    vector<int> above_average;

    for (int i = 0; i < temps.size(); ++i){
        if (temps[i] > mean_temp){
            above_average.push_back(i);
        }
    }

    cout << above_average.size() << endl;
    cout << above_average;
}