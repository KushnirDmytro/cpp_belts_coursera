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


//У каждого из нас есть ежемесячные дела, каждое из которых нужно выполнять в конкретный день каждого месяца:
// оплата счетов за электричество, абонентская плата за связь и пр. Вам нужно реализовать работу со списком таких дел,
// а именно, обработку следующих операций:
//
//ADD is
//Добавить дело с названием s в день i.
//
//NEXT
//Закончить текущий месяц и начать новый. Если новый месяц имеет больше дней, чем текущий,
// добавленные дни изначально не будут содержать дел. Если же в новом месяце меньше дней,
// дела со всех удаляемых дней необходимо будет переместить на последний день нового месяца.
//
//Обратите внимание, что количество команд этого типа может превышать 11.
//
//DUMP i
//Вывести все дела в день i.
//
//Изначально текущим месяцем считается январь. Количества дней в месяцах соответствуют
// Григорианскому календарю с той лишь разницей, что в феврале всегда 28 дней.
//
//Формат ввода
//Сначала число операций Q, затем описания операций.
//
//Названия дел s уникальны и состоят только из латинских букв, цифр и символов подчёркивания.
// Номера дней i являются целыми числами и нумеруются от 1 до размера текущего месяца.
//
//Формат вывода
//Для каждой операции типа DUMP в отдельной строке выведите количество дел в соответствующий день,
// а затем их названия, разделяя их пробелом. Порядок вывода дел в рамках каждой операции значения не имеет.
/*
 in:
12
ADD 5 Salary
ADD 31 Walk
ADD 30 WalkPreparations
NEXT
DUMP 5
DUMP 28
NEXT
DUMP 31
DUMP 30
DUMP 28
ADD 28 Payment
DUMP 28

 out:
 1 Salary
2 WalkPreparations Walk
0
0
2 WalkPreparations Walk
3 WalkPreparations Walk Payment



 14
NEXT
NEXT
NEXT
NEXT
NEXT
NEXT
ADD 31 Gallery
DUMP 31
DUMP 30
NEXT
DUMP 31
DUMP 30
DUMP 29
DUMP 28



1 Gallery
0
1 Gallery
0
0
0
 */


template<class T> ostream& operator<<(ostream& os, vector<T> v){
    for (auto &s: v){
        cout << s << " ";
    }
    return os;
}

enum commands{
    ADD, NEXT, DUMP
};

map<string, commands> known_commands{
        {"ADD", ADD},
        {"NEXT",NEXT},
        {"DUMP",DUMP}
};
//В Январе - 31 день
//В Феврале - 28 дней
//В Марте - 31 день
//В Апреле - 30 дней
//В Мае - 31 день
//В Июне - 30 дней
//В Июле - 31 день
//В Августе - 31 день
//В Сентябре - 30 дней
//В Октябре - 31 день
//В Ноябре - 30 дней
//В Декабре - 31 день
const vector<int> months{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main() {

    using daytasks = vector<string>;
    vector<daytasks> organiser(months[0]);
    int N;
    string command;
    int command_num_arg;
    string command_string_arg;
    int this_month {0};
    cin >> N;

    for (int i = 0; i < N; ++i){
        cin >> command;
        commands com = known_commands[command];
        switch (com){
            case ADD:
                cin >> command_num_arg >> command_string_arg;
                organiser[command_num_arg - 1].emplace_back(command_string_arg);
                break;

            case NEXT:{
                ++this_month;
                if (this_month > 11){
                    this_month = 0;
                }

                if (months[this_month] < organiser.size()){
                    for (int i = months[this_month]; i < organiser.size(); ++i){
                        organiser[months[this_month] - 1].insert(organiser[months[this_month] - 1].end(), organiser[i].begin(), organiser[i].end());
                    }
                }

                organiser.resize(months[this_month]);
            }

                break;

            case DUMP:
                cin >> command_num_arg;
                cout << organiser[command_num_arg - 1].size() << " ";
                if (organiser[command_num_arg - 1].size() > 0){
                    cout << organiser[command_num_arg - 1] ;
                }
                cout << endl;

                break;
        }
    }
}
