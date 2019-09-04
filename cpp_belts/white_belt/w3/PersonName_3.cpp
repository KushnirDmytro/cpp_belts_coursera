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


//Дополните класс Person из задачи «Имена и фамилии — 2»
// конструктором, позволяющим задать имя и фамилию человека при рождении, а также сам год рождения. Класс не должен иметь конструктора по умолчанию.
//
//При получении на вход года, который меньше года рождения:
//
//методы GetFullName и GetFullNameWithHistory должны отдавать "No person";
//методы ChangeFirstName и ChangeLastName должны игнорировать запрос.
//Кроме того, необходимо объявить константными все методы, которые по сути ими являются.


class Person {
private:
    int birth_year;
    map<int, string> first_name_records_;
    map<int, string> last_name_records_;
public:
    Person( const string &f_name, const string &l_name, int year ) :
            birth_year{year},
            first_name_records_{ {year, f_name} },
            last_name_records_{ {year, l_name} }{
    }

    void ChangeFirstName(int year, const string& first_name) {
        // добавить факт изменения имени на first_name в год year
        if (year < birth_year){
            return;
        }
        first_name_records_[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        if (year < birth_year){
            return;
        }
        last_name_records_[year] = last_name;
        // добавить факт изменения фамилии на last_name в год year
    }
    string GetFullName(int year) const {
        if (year < birth_year){
            return "No person";
        }
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
    string GetFullNameWithHistory(int year) const {
        // получить все имена и фамилии по состоянию на конец года year
        if (year < birth_year){
            return "No person";
        }
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

};

template<class T> ostream& operator<<(ostream& os, vector<T> v){
    for (const auto &s: v){
        cout << s << " ";
    }
    return os;
}
//
//int main() {
//    Person person("Polina", "Sergeeva", 1960);
//    for (int year : {1959, 1960}) {
//        cout << person.GetFullNameWithHistory(year) << endl;
//    }
//
//    person.ChangeFirstName(1965, "Appolinaria");
//    person.ChangeLastName(1967, "Ivanova");
//    for (int year : {1965, 1967}) {
//        cout << person.GetFullNameWithHistory(year) << endl;
//    }
//
//    return 0;
//}

//No person
//Polina Sergeeva
//Appolinaria (Polina) Sergeeva
//Appolinaria (Polina) Ivanova (Sergeeva)
