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
6
first
second
first
third
second
second

 out:
3

 */



//Дан набор строк. Найдите количество уникальных строк в этом наборе.
//
//Формат ввода
//Сначала вводится количество строк N, затем — сами N строк, разделённые пробелом. Все строки состоят лишь из латинских букв, цифр и символов подчёркивания.
//
//Формат вывода
//Выведите единственное целое число — количество уникальных строк в данном наборе.


int main() {


    int N;
    cin >> N;

    set<string> unique_words;
    string s_buf;

    for (int i = 0; i < N; ++i) {
        cin >> s_buf;
        unique_words.insert(s_buf);
    }
    cout << unique_words.size() << endl;

}
