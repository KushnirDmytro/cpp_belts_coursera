//
// Created by dkushn on 14.08.19.
//

#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

//enum class Gender {
//    FEMALE,
//    MALE
//};
//
//struct Person {
//    int age;  // возраст
//    Gender gender;  // пол
//    bool is_employed;  // имеет ли работу
//};

bool operator<(const Person& lhs, const Person &rhs){
    return lhs.age < rhs.age;
}

//template <typename InputIt>
//int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
//    if (range_begin == range_end) {
//        return 0;
//    }
//    vector<typename InputIt::value_type> range_copy(range_begin, range_end);
//    auto middle = begin(range_copy) + range_copy.size() / 2;
//    nth_element(
//            begin(range_copy), middle, end(range_copy),
//            [](const Person& lhs, const Person& rhs) {
//                return lhs.age < rhs.age;
//            }
//    );
//    return middle->age;
//}

auto accum_age = [](int accum, const Person& per){
    return accum + per.age;
};



void PrintStats(vector<Person> persons){
    sort(persons.begin(), persons.end() );
    cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << endl;

    auto female_range_rhs = partition(persons.begin(), persons.end(), [](const Person& per){ return per.gender == Gender::FEMALE;});

    cout << "Median age for females = " << ComputeMedianAge(persons.begin(), female_range_rhs) << endl;
    cout << "Median age for males = " << ComputeMedianAge(female_range_rhs, persons.end()) << endl;

    auto employed_female_rhs = partition(persons.begin(), female_range_rhs, [](const Person& per){ return per.is_employed;});

    cout << "Median age for employed females = " << ComputeMedianAge(persons.begin(), employed_female_rhs) << endl;
    cout << "Median age for unemployed females = " << ComputeMedianAge(employed_female_rhs, female_range_rhs) << endl;

    auto employed_male_rhs = partition(female_range_rhs, persons.end(), [](const Person& per){ return per.is_employed;});

    cout << "Median age for employed males = " << ComputeMedianAge(female_range_rhs, employed_male_rhs) << endl;
    cout << "Median age for unemployed males = " << ComputeMedianAge(employed_male_rhs, persons.end()) << endl;
}

int main() {
    vector<Person> persons = {
            {31, Gender::MALE, false},
            {40, Gender::FEMALE, true},
            {24, Gender::MALE, true},
            {20, Gender::FEMALE, true},
            {80, Gender::FEMALE, false},
            {78, Gender::MALE, false},
            {10, Gender::FEMALE, false},
            {55, Gender::MALE, true},
    };
    PrintStats(persons);
    return 0;
}
