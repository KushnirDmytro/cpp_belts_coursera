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


//юди стоят в очереди, но никогда не уходят из её начала, зато могут приходить в конец и уходить оттуда.
// Более того, иногда некоторые люди могут прекращать и начинать беспокоиться из-за того, что очередь не продвигается.
//
//Реализуйте обработку следующих операций над очередью:
//
//WORRY i: пометить i-го человека с начала очереди (в нумерации с 0) как беспокоящегося;
//QUIET i: пометить i-го человека как успокоившегося;
//COME k: добавить k спокойных человек в конец очереди;
//COME -k: убрать k человек из конца очереди;
//WORRY_COUNT: узнать количество беспокоящихся людей в очереди.
//Изначально очередь пуста.
//
//Формат ввода
//Количество операций Q, затем описания операций.
//
//Для каждой операции WORRY i и QUIET i гарантируется, что человек с номером i существует в очереди на момент операции.
//
//Для каждой операции COME -k гарантируется, что k не больше текущего размера очереди.
//
//Формат вывода
//Для каждой операции WORRY_COUNT выведите одно целое число — количество беспокоящихся людей в очереди.

/*
 in: 8
COME 5
WORRY 1
WORRY 4
COME -2
WORRY_COUNT
COME 3
WORRY 3
WORRY_COUNT

 out:
 1
2
 */


template<class T> ostream& operator<<(ostream& st, vector<T> v){
    for (auto &s: v){
        cout << s << " ";
    }
    cout << endl;
}

enum commands{
    WORRY, QUIET, COME, WORRY_COUNT
};

map<string, commands> known_commands{
        {"QUIET", QUIET},
        {"WORRY",WORRY},
        {"COME",COME},
        {"WORRY_COUNT",WORRY_COUNT}
};

int main() {
    vector<bool> q;
    int N, temp, s{0};
    string command;
    int command_arg;

    cin >> N;

    for (int i = 0; i < N; ++i){
        cin >> command;
        commands com = known_commands[command];
        if (com != WORRY_COUNT) {
            cin >> command_arg;
        }
        switch (com){
            case WORRY:
                q[command_arg] = true;
                break;
            case QUIET:
                q[command_arg] = false;
                break;
            case COME:
                q.resize(q.size() + command_arg);
                break;
            case WORRY_COUNT:
                cout << accumulate(q.begin(),q.end(),0) << endl;
                break;
        }
    }
}
