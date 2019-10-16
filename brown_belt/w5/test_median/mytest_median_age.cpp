//
// Created by dkushn on 15.10.19.
//

#include "test_runner.h"

#include <vector>
#include "A_correct.cpp"
#include "B_correct.cpp"
#include "bug1_bad.cpp"
#include "bug2_bad.cpp"
#include "bug3_bad.cpp"
#include "bug4_bad.cpp"
#include "bug5_bad.cpp"
#include "bug6_bad.cpp"

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


void assert_stream_has_vector_cntnt(const vector<string> &expected, stringstream &oss ){
    string buf;
    auto it = expected.begin();
    while (getline(oss, buf) ){
        cout << buf << endl;
        cout << *it << endl;
        ASSERT_EQUAL(*(it), buf);
        it = next(it, 1);
    }
};

void Test1(){
        vector<Person> persons {
//            {31, Gender::MALE, false},
//            {40, Gender::FEMALE, true},
//            {24, Gender::MALE, true},
//            {20, Gender::FEMALE, true},
//            {80, Gender::FEMALE, false},
//            {78, Gender::MALE, false},
//            {10, Gender::FEMALE, false},
//            {55, Gender::MALE, true}
        };

        stringstream oss;

//        PrintStats(persons, oss);

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
//    vector<string> expected {
//            "Median age = 0",
//            "Median age for females = 0",
//            "Median age for males = 0",
//            "Median age for employed females = 0",
//            "Median age for unemployed females = 0",
//            "Median age for employed males = 0",
//            "Median age for unemployed males = 0"
//    };

        bad1::PrintPerson(iss, oss);

    assert_stream_has_vector_cntnt(expected, oss);
};


void B3_and_4_reading_order_preserved(){
vector<B::Person> ps{
        {31, B::Gender::FEMALE, false},
        {31, B::Gender::MALE, false},
        {31, B::Gender::FEMALE, true},
        {31, B::Gender::MALE, true}
};

vector<string> input {
    "4 \n",
    "31 0 0 \n",
    "31 1 0 \n",
    "31 0 1 \n",
    "31 1 1 \n"
};
stringstream iss;
for (const auto &per_str : input){
    iss << per_str;
}
    vector<B::Person> result = B::ReadPersons(iss);
    ASSERT_EQUAL(result, ps);
};

    bool operator==(const B::AgeStats &lhs, const B::AgeStats &rhs){
        return lhs.employed_females == rhs.employed_females &&
        lhs.employed_males == rhs.employed_males &&
        lhs.females == rhs.females &&
        lhs.males == rhs.males &&
        lhs.total == rhs.total &&
        lhs.unemployed_females == rhs.unemployed_females &&
        lhs.unemployed_males == rhs.unemployed_males;
    }

void test5_6ComputeMedianEnds(){
    vector<B::Person> persons {
            {31, B::Gender::MALE, false},
            {40, B::Gender::FEMALE, true},
            {24, B::Gender::MALE, true},
            {20, B::Gender::FEMALE, true},
            {80, B::Gender::FEMALE, false},
            {78, B::Gender::MALE, false},
            {10, B::Gender::FEMALE, false},
            {55, B::Gender::MALE, true}
    };
    B::AgeStats as = B::ComputeStats(persons);
    B::AgeStats as_expect {
        40,
        40,
        55,
        40,
        80,
        55,
        78
    };
    ASSERT( as_expect ==  as);
}

void test1_EmptyRange(){
    vector<B::Person> persons {
    };
    int stat = B::ComputeMedianAge(persons.begin(), persons.end());

    ASSERT( stat == 0);
}


void test1_s1_range(){
    vector<B::Person> persons {
            {1, B::Gender::MALE, false}
    };
    int stat = B::ComputeMedianAge(persons.begin(), persons.end());

    ASSERT( stat == 1);
}

void test2_OddSizeRange(){
    vector<B::Person> persons {
            {1, B::Gender::MALE, false},
            {2, B::Gender::FEMALE, true},
            {3, B::Gender::MALE, true},
            {4, B::Gender::FEMALE, true},
            {5, B::Gender::FEMALE, false}
    };
    int stat = B::ComputeMedianAge(persons.begin(), persons.end());

    ASSERT( stat == 3);
}

void testSwapOrder(){
    B::AgeStats as_expect {
            40,
            40,
            55,
            40,
            80,
            55,
            78
    };
    stringstream ss;
    B::PrintStats(as_expect, ss);
    vector<string> expected {
            "Median age = 40",
            "Median age for females = 40",
            "Median age for males = 55",
            "Median age for employed females = 40",
            "Median age for unemployed females = 80",
            "Median age for employed males = 55",
            "Median age for unemployed males = 78"
    };
    assert_stream_has_vector_cntnt(expected, ss);
    }

int main(){
    TestRunner tr;
//    RUN_TEST(tr, Test1);
    RUN_TEST(tr, test1_EmptyRange);
    RUN_TEST(tr, test1_s1_range);
    RUN_TEST(tr, test2_OddSizeRange);
    RUN_TEST(tr, B3_and_4_reading_order_preserved);
    RUN_TEST(tr, test5_6ComputeMedianEnds);
//    RunMedianAge(cin, cout);
}