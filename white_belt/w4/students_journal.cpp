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
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;


//Определите структуру «Студент» со следующими полями: имя, фамилия, день, месяц и год рождения.
// Создайте вектор из таких структур, заполните его из входных данных и затем по запросам выведите нужные поля.
//
//Формат ввода
//
//Первая строка содержит одно целое число N от 0 до 10000 — число студентов.
//
//Далее идут N строк, каждая из которых содержит две строки длиной от 1 до 15 символов —
// имя и фамилию очередного студента, и три целых числа от 0 до 1000000000 — день, месяц и год рождения.
//
//Следующая строка содержит одно целое число M от 0 до 10000 — число запросов.
//
//Следующие M строк содержат строку длиной от 1 до 15 символов — запрос, и целое число от 0 до 1000000000 —
// номер студента (нумерация начинается с 1).
//
//Формат вывода
//
//Для запроса вида name K, где K от 1 до N, выведите через пробел имя и фамилию K-го студента.
//
//Для запроса вида date K, где K от 1 до N, выведите через точку день, месяц и год рождения K-го студента.
//
//Для остальных запросов выведите bad request.

/*
in:
 3
Ivan Ivanov 1 1 1901
Petr Petrox 2 2 1902
Alexander Sidorov 3 3 1903
4
name 1
date 3
mark 5
wrong 1


 out:

Ivan Ivanov
3.3.1903
bad request

         */

struct Date{
    int year;
    int month;
    int day;
};

struct Student{
    string name;
    string surname;
    Date birth_date;
};

enum Requests{
    date, name
};

struct Request_input{
    string name;
    int k;
};

map<string, Requests> known_requests{
        {"date", date},
        {"name", name}
};

int main()
{
    int N;
    cin >> N;
    vector<Student> students(N);
    for (auto &stud: students){
        cin >> stud.name >> stud.surname >> stud.birth_date.day >> stud.birth_date.month >> stud.birth_date.year;
    }
    int M;
    cin >> M;
    Request_input req;
    Requests req_deciphered;
    for (int j = 0; j < M; ++j){
        cin >> req.name;
        cin >> req.k;
        req.k--;
        if (known_requests.count(req.name) != 0 && req.k < N && req.k >= 0){
            req_deciphered = known_requests[req.name];
            switch (req_deciphered){
                case (date):
                    cout << students[req.k].birth_date.day << '.' <<
                         students[req.k].birth_date.month << '.' <<
                         students[req.k].birth_date.year << endl;
                    break;
                case (name):
                    cout << students[req.k].name << ' ' << students[req.k].surname << endl;
                    break;
            }
        }
        else{
            cout << "bad request" << endl;
        }
    }
}