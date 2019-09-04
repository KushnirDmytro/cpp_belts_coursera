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


//Реализуйте класс для человека, поддерживающий историю изменений человеком своих фамилии и имени.

//Считайте, что в каждый год может произойти не более одного изменения фамилии и не более одного изменения имени.
// При этом с течением времени могут открываться всё новые факты из прошлого человека, поэтому года́ в последовательных вызовах методов ChangeLastName и ChangeFirstName не обязаны возрастать.
//
//Гарантируется, что все имена и фамилии непусты.
//
//Строка, возвращаемая методом GetFullName, должна содержать разделённые одним пробелом имя и фамилию человека по состоянию на конец данного года.
//
//Если к данному году не случилось ни одного изменения фамилии и имени, верните строку "Incognito".
//Если к данному году случилось изменение фамилии, но не было ни одного изменения имени, верните "last_name with unknown first name".
//Если к данному году случилось изменение имени, но не было ни одного изменения фамилии, верните "first_name with unknown last name".


class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        // добавить факт изменения имени на first_name в год year
        first_name_records_[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        last_name_records_[year] = last_name;
        // добавить факт изменения фамилии на last_name в год year
    }
    string GetFullName(int year) {
        // получить имя и фамилию по состоянию на конец года year
        string  f_name = get_name_up_to_year(year, first_name_records_);
        string  l_name = get_name_up_to_year(year, last_name_records_);
        if (l_name.empty() && f_name.empty()){
            return "Incognito";
        }else if (l_name.empty()) {
            return f_name + " with unknown last name";
        } else if (f_name.empty()){
            return l_name + " with unknown first name";
        } else {
            return f_name + " " + l_name;
        }
    }
private:

    string get_name_up_to_year(int year, const map<int, string> &records) const{
        string name_state;
        for (auto &name_record: records){
            if (name_record.first <= year){
                name_state = name_record.second;
            } else{
                break;
            }
        }
        return name_state;
    }

    map<int, string> first_name_records_;
    map<int, string> last_name_records_;
};

template<class T> ostream& operator<<(ostream& os, vector<T> v){
    for (const auto &s: v){
        cout << s << " ";
    }
    return os;
}

//int main() {
//    Person person;
//
//    person.ChangeFirstName(1965, "Polina");
//    person.ChangeLastName(1967, "Sergeeva");
//    for (int year : {1900, 1965, 1990}) {
//        cout << person.GetFullName(year) << endl;
//    }
//
//    person.ChangeFirstName(1970, "Appolinaria");
//    for (int year : {1969, 1970}) {
//        cout << person.GetFullName(year) << endl;
//    }
//
//    person.ChangeLastName(1968, "Volkova");
//    for (int year : {1969, 1970}) {
//        cout << person.GetFullName(year) << endl;
//    }
//
//    return 0;
//}

// expect: Incognito
//Polina with unknown last name
//Polina Sergeeva
//Polina Sergeeva
//Appolinaria Sergeeva
//Polina Volkova
//Appolinaria Volkova