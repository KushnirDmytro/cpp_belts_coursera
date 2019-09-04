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
    string GetFullNameWithHistory(int year) {
        // получить все имена и фамилии по состоянию на конец года year
        vector<string>  f_names = get_all_names_up_to_year(year, first_name_records_);
        vector<string>  l_names = get_all_names_up_to_year(year, last_name_records_);
        if (l_names.empty() && f_names.empty()){
            return "Incognito";
        }else if (l_names.empty()) {
            return BuildNameFromHistory(f_names) + " with unknown last name";
        } else if (f_names.empty()){
            return BuildNameFromHistory(l_names) + " with unknown first name";
        } else {
            return BuildNameFromHistory(f_names) + " " + BuildNameFromHistory(l_names);
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

    vector<string> DeduplicateNamesListReverse(const vector<string> &names_seq) const {
        vector<string> dedup_reverse;
        auto prev = names_seq.back();
        dedup_reverse.push_back(prev);
        for (auto it = names_seq.end() - 2; it >= names_seq.begin(); --it){
            if (*it != prev){
                dedup_reverse.push_back(*it);
            }
            prev = *it;
        }
        return dedup_reverse;
    }

    string BuildNameFromHistory(const vector<string> &names) const{
        vector<string> dedup_names = DeduplicateNamesListReverse(names);
        if (dedup_names.size() == 1){
            return dedup_names[0];
        }
        else{
            string buf {dedup_names.front() + " ("};
            string prev_name = dedup_names.front();
            for (auto it = dedup_names.begin() + 1; it < dedup_names.end() ; ++it){
                if (*it != prev_name){
                    buf += *it + ", ";
                }
                prev_name = *it;
            }
            buf.resize(buf.size() - 1);
            buf.back() = ')'; // replace last ',' with ')'
            return buf;
        }
    }

    vector<string> get_all_names_up_to_year(int year, const map<int, string> &records) const{
        vector<string> names_state;
        for (auto &name_record: records){
            if (name_record.first <= year){
                names_state.push_back(name_record.second);
            } else{
                break;
            }
        }
        return names_state;
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
//        cout << person.GetFullNameWithHistory(year) << endl;
//    }
//
//    person.ChangeFirstName(1970, "Appolinaria");
//    for (int year : {1969, 1970}) {
//        cout << person.GetFullNameWithHistory(year) << endl;
//    }
//
//    person.ChangeLastName(1968, "Volkova");
//    for (int year : {1969, 1970}) {
//        cout << person.GetFullNameWithHistory(year) << endl;
//    }
//
//    person.ChangeFirstName(1990, "Polina");
//    person.ChangeLastName(1990, "Volkova-Sergeeva");
//    cout << person.GetFullNameWithHistory(1990) << endl;
//
//    person.ChangeFirstName(1966, "Pauline");
//    cout << person.GetFullNameWithHistory(1966) << endl;
//
//    person.ChangeLastName(1960, "Sergeeva");
//    for (int year : {1960, 1967}) {
//        cout << person.GetFullNameWithHistory(year) << endl;
//    }
//
//    person.ChangeLastName(1961, "Ivanova");
//    cout << person.GetFullNameWithHistory(1967) << endl;
//
//    return 0;
//}

// Incognito
//Polina with unknown last name
//Polina Sergeeva
//Polina Sergeeva
//Appolinaria (Polina) Sergeeva
//Polina Volkova (Sergeeva)
//Appolinaria (Polina) Volkova (Sergeeva)
//Polina (Appolinaria, Polina) Volkova-Sergeeva (Volkova, Sergeeva)
//Pauline (Polina) with unknown last name
//Sergeeva with unknown first name
//Pauline (Polina) Sergeeva
//Pauline (Polina) Sergeeva (Ivanova, Sergeeva)