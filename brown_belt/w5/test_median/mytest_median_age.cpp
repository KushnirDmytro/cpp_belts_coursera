//
// Created by dkushn on 15.10.19.
//

#include "test_runner.h"

#include <vector>
#include "A_correct.cpp"

ostream& operator<<(ostream& os, Gender gen){
    os << (gen == Gender::MALE);
    return os;
}


bool operator<(const Person& lhs, const Person &rhs){
    return lhs.age < rhs.age;
}

void PrintStats(vector<Person> persons, ostream& os){
    sort(persons.begin(), persons.end() );
    os << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << endl;

    auto female_range_rhs =
            partition(persons.begin(),
                    persons.end(),
                    [](const Person& per){ return per.gender == Gender::FEMALE;});

    os << "Median age for females = " << ComputeMedianAge(persons.begin(), female_range_rhs) << endl;
    os << "Median age for males = " << ComputeMedianAge(female_range_rhs, persons.end()) << endl;

    auto employed_female_rhs =
            partition(persons.begin(),
                    female_range_rhs,
                    [](const Person& per){ return per.is_employed;});

    os << "Median age for employed females = " << ComputeMedianAge(persons.begin(), employed_female_rhs) << endl;
    os << "Median age for unemployed females = " << ComputeMedianAge(employed_female_rhs, female_range_rhs) << endl;

    auto employed_male_rhs =
            partition(female_range_rhs,
                    persons.end(),
                    [](const Person& per){ return per.is_employed;});

    os << "Median age for employed males = " << ComputeMedianAge(female_range_rhs, employed_male_rhs) << endl;
    os << "Median age for unemployed males = " << ComputeMedianAge(employed_male_rhs, persons.end()) << endl;
}


void Test1(){
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

        stringstream oss;
        PrintStats(persons, oss);
        stringstream iss;
        iss << persons.size() << '\n';
        for (const auto& per: persons)
            iss << per.age << ' ' << per.gender << ' ' << per.is_employed << '\n';

        vector<string> expected {
                "Median age = 40",
                "Median age for females = 40",
                "Median age for males = 55",
                "Median age for employed females = 40",
                "Median age for unemployed females = 80",
                "Median age for employed males = 55",
                "Median age for unemployed males = 78"
        };


        string buf;
        auto it = expected.begin();
    while (getline(oss, buf) ){
        ASSERT_EQUAL(*(it), buf);
        it = next(it, 1);
    }


};

int main(){
    TestRunner tr;
    RUN_TEST(tr, Test1);
//    RunMedianAge(cin, cout);
}