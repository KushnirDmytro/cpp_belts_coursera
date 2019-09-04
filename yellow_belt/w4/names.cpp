//
// Created by dkushn on 18.08.19.
//

//
// Created by dkushn on 14.08.19.
//

#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <map>


using namespace std;

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        f_n[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        l_n[year] = last_name;
    }
    string GetFullName(int year) {
        string f_name = FindNameByYear(year, f_n);
        string l_name = FindNameByYear(year, l_n);
        if (f_name.empty()){
            if (l_name.empty())
                return "Incognito";
            else
                return l_name + " with unknown first name";
        } else {
            if (l_name.empty()){
                return f_name + " with unknown last name";
            } else {
                return f_name + " " + l_name;
            }
        }
        // получить имя и фамилию по состоянию на конец года year
        // с помощью двоичного поиска
    }
private:

    string FindNameByYear(const int year, const map<int, string> &m){
        string res{};
        auto l_b = m.lower_bound(year);
        if (l_b->first == year){
            res = l_b->second;
            return res;
        }
        else {
            if (l_b != m.begin()){
                res = prev(l_b)->second;
            }
        }
        return res;
    }

    map<int, string> f_n;
    map<int, string> l_n;
    // приватные поля
};


int main() {
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    return 0;
}

/*
Incognito
Polina with unknown last name
Polina Sergeeva
Polina Sergeeva
Appolinaria Sergeeva
Polina Volkova
Appolinaria Volkova

 * */